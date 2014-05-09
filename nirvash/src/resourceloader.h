#ifndef _NEPGEAR_RESOURCE_LOADER_H_
#define _NEPGEAR_RESOURCE_LOADER_H_

#include "entity.h"
#include "model/mesh.h"
#include "utils/thread.h"
#include "utils/logger.h"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Nepgear
{
	namespace Convert
	{
		void ai_to_glm_mat4(glm::mat4 *out, aiMatrix4x4 in)
		{
			(*out)[0] = glm::vec4(in.a1, in.a2, in.a3, in.a4);
			(*out)[1] = glm::vec4(in.b1, in.b2, in.b3, in.b4);
			(*out)[2] = glm::vec4(in.c1, in.c2, in.c3, in.c4);
			(*out)[3] = glm::vec4(in.d1, in.d2, in.d3, in.d4);
		}

		void ai_to_glm_vec2(glm::vec2 *out, aiVector2t<float> in)
		{
			out->x = in.x;
			out->y = in.y;
		}

		void ai_to_glm_vec3(glm::vec3 *out, aiVector3t<float> in)
		{
			out->x = in.x;
			out->y = in.y;
			out->z = in.z;
		}

		void ai_to_glm_vec4(glm::vec4 *out, aiColor4t<float> in)
		{
			out->r = in.r;
			out->g = in.g;
			out->b = in.b;
			out->a = in.a;
		}
	}
}

namespace Nepgear
{
	template<typename T>
	class ResourceLoader
	{
	public:
		ResourceLoader() : mesh_count(0), progress(0.0f), done(false) {}

		std::vector<std::string> queue;
		std::vector<T*> loaded;

		int mesh_count;
		float progress; // 0.0-1.0. float(queue.size() / loaded.size())
		bool done; // finished processing entire queue, thread terminated.

		void Process()
		{
			handle = new Thread(load, (void*)this);
		}

	protected:
		static void recursive_load(int *count, T *current, const struct aiScene *sc, const struct aiNode* nd)
		{
			using namespace Nepgear::Convert;
			Nepgear::Logger log(NULL);
			ai_to_glm_mat4(&current->xform, nd->mTransformation);
			
			for (unsigned n = 0; n < nd->mNumMeshes; ++n)
			{
				const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];

				// *count++ is parsed wrong and throws a warning/error.
				*count = (*count)+1;
				T m;
				m.material_id = mesh->mMaterialIndex;

				log.debug("[ResourceLoader] Mesh Faces: %d", mesh->mNumFaces);

				for (unsigned t = 0; t < mesh->mNumFaces; ++t) {
					const struct aiFace* face = &mesh->mFaces[t];

					for(unsigned i = 0; i < face->mNumIndices; i++)
					{
						int idx = face->mIndices[i];
						Nepgear::Vertex v;

						ai_to_glm_vec3(&v.position, mesh->mVertices[idx]);

						if (mesh->mNormals != NULL)
							ai_to_glm_vec3(&v.normal, mesh->mNormals[idx]);

						if (mesh->HasTextureCoords(0))
						{
							glm::vec3 tmp;
							ai_to_glm_vec3(&tmp, mesh->mTextureCoords[0][idx]);
							v.tex_coords = glm::vec2(tmp.x, tmp.y);
						}

						if (mesh->mColors[0] != NULL)
							ai_to_glm_vec4(&v.color, mesh->mColors[0][idx]);

						std::vector<Nepgear::Vertex> *list;
						
						switch (face->mNumIndices)
						{
							case 1: list = &m.points; break;
							case 2: list = &m.lines; break;
							case 3: list = &m.triangles; break;
							default: continue; break;
						}
						list->push_back(v);
					}
				}
				m.parent = current;
				current->children.push_back(m);
			}
			
			for (unsigned n = 0; n < nd->mNumChildren; ++n)
			{
				if (current->children.size() <= n)
				{
					T m;
					//m.depth = current->depth;
					m.parent = current;
					current->children.push_back(m);
				}
				recursive_load(count, &current->children[n], sc, nd->mChildren[n]);
			}
		}

		static void load(void* data)
		{
			ResourceLoader<T> *self = (ResourceLoader<T>*)data;
			Logger log(NULL);

			Assimp::Importer imp;
			const aiScene *scene;
			auto it = self->queue.begin();
			for ( ; it != self->queue.end(); ++it)
			{
				log.debug(
					"[ResourceLoader] Loading scene: \"%s\"",
					(*it).c_str()
				);

				scene = imp.ReadFile(
					(*it).c_str(),
					aiProcess_Triangulate | aiProcess_GenSmoothNormals
				);

				if (!scene)
				{
					log.warn(
						"[ResourceLoader] Error loading scene: \"%s\"",
						(*it).c_str()
					);
				}
				else
				{
					using namespace Nepgear::Convert;
					T *mesh = new T();
					ai_to_glm_mat4(&mesh->xform, scene->mRootNode->mTransformation);
					recursive_load(&self->mesh_count, mesh, scene, scene->mRootNode);
					self->loaded.push_back(mesh);
					self->progress = float(self->queue.size() / self->loaded.size());
				}
				log.debug("[ResourceLoader] Loaded %d mesh(es)", self->mesh_count);
				self->mesh_count = 0;
			}
			log.debug("[ResourceLoader] Loaded %ld scene(s)", self->loaded.size());
			self->queue.clear();
			self->done = true;
		}
		
		Thread *handle;
	};
}

#endif

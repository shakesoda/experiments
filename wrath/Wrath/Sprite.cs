using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace Wrath
{
	public class Sprite : Entity
	{
		protected Quad m_buffer;
		protected Material m_material;
		protected uint m_texture;
		protected Vector2 m_dimensions;

		public Sprite()
		{
			// todo
		}
		
		public void Load(string path)
		{
			GL.GenTextures(1, out this.m_texture);
			GL.BindTexture(TextureTarget.Texture2D, this.m_texture);

			// bring your own png. todo: fix working directory or something.
			Bitmap bitmap = new Bitmap(path);
			m_dimensions = new Vector2(bitmap.Width, bitmap.Height);

			BitmapData data = bitmap.LockBits(
				new Rectangle(0, 0, bitmap.Width, bitmap.Height),
				ImageLockMode.ReadOnly,
				System.Drawing.Imaging.PixelFormat.Format32bppArgb
			);
			// protected BitmapData m_bitmap_data;
			GL.TexImage2D(
				TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba,
				data.Width, data.Height, 0,
				OpenTK.Graphics.OpenGL.PixelFormat.Bgra,
				PixelType.UnsignedByte, data.Scan0
			);

			bitmap.UnlockBits(data);
			bitmap.Dispose();

			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);  
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);  

			GL.MatrixMode(MatrixMode.Projection);
		}

		public void Render()
		{
			GL.Translate(this.m_position);
			GL.Begin(BeginMode.Quads);
			{
				GL.TexCoord2(0, 0);
				GL.Vertex2(0, 0);
				GL.TexCoord2(1, 0);
				GL.Vertex2(this.m_dimensions.X, 0);
				GL.TexCoord2(1, 1);
				GL.Vertex2(this.m_dimensions.X, this.m_dimensions.Y);
				GL.TexCoord2(0, 1);
				GL.Vertex2(0, this.m_dimensions.Y);
			}
			GL.End();
		}
	}
}
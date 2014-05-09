using System;
using System.IO;
using OpenTK.Graphics.OpenGL;

namespace Wrath
{
	public class Material
	{
		public Material ()
		{
			FileStream f = File.OpenRead("france");
		}
		
		~Material()
		{
			GL.DeleteProgram(m_program);
		}
		
		public void Bind()
		{
		}
		
		protected uint m_program;
	}
}



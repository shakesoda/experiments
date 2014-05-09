using System;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace Wrath
{
	public class Quad : Entity
	{
		public Quad ()
		{
		}

		public void SetSize(Vector2 size)
		{
			m_size = size;
		}
		
		public Vector2 GetSize()
		{
			return m_size;
		}
		
		public override void Initialize()
		{
			m_size = new Vector2(16, 16);
			float[] data = {
				0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	
				1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	
				1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			};

			GL.GenVertexArrays(1, out m_vao);
			GL.BindVertexArray(m_vao);

			GL.GenBuffers(1, out m_buffer);
			GL.BindBuffer(BufferTarget.ArrayBuffer, m_buffer);
			GL.BufferData(BufferTarget.ArrayBuffer,
				// ugly :(
				(IntPtr)(5*4*sizeof(float)), (IntPtr)data[0],
				BufferUsageHint.StaticRead
			);

			GL.EnableVertexAttribArray(0);
			GL.EnableVertexAttribArray(1);
			GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 5*sizeof(float), 0);
			GL.VertexAttribPointer(1, 2, VertexAttribPointerType.Float, false, 5*sizeof(float), 3*sizeof(float));
		}
		
		public override void Update(FrameEventArgs e)
		{
			
		}
		
		public override void Draw(FrameEventArgs e)
		{
			GL.BindVertexArray(m_vao);
			GL.DrawArrays(BeginMode.TriangleStrip, 0, 4);
		}
		
		protected uint m_vao;
		protected uint m_buffer;
		protected Vector2 m_size;
	}
}

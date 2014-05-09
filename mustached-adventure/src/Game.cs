using System;
using System.Collections.Generic;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Audio;
using OpenTK.Audio.OpenAL;
using OpenTK.Input;

namespace Wrath
{
	class Game : GameWindow
	{
		public Game(int width, int height) :
			base(
				width, height, GraphicsMode.Default, "Game",
				GameWindowFlags.Default, DisplayDevice.Default,
				3, 0, GraphicsContextFlags.Default
			)
		{
			m_shader = new Shader();
		}

		protected int m_buffer;
		protected Shader m_shader;
		protected int m_vao;

		protected List<Quad> m_objects = new List<Quad>();
		
		protected override void OnLoad(EventArgs e)
		{
			base.OnLoad(e);
						
			VSync = VSyncMode.On;
			Console.WriteLine("GL Version " + GL.GetString(StringName.Version));
			
			GL.ClearColor( Color4.CornflowerBlue );
			GL.Enable(EnableCap.DepthTest);

			for( int i = 0; i < 6; i++ ) {
				Quad newObject = new Quad();
				Random rand = new Random();

				newObject.SetSize( new Vector2(32, 32) );
				newObject.SetPosition( new Vector3( rand.Next(32,480), rand.Next(32, 200), 0 )); 

				m_objects.Add( newObject );
			}

			// TODO: read from file
			string vss =
				"#version 130\n"+
				"in vec4 in_position;"+
				"in vec3 in_color;\n"+
				"out vec3 color;\n"+
				"uniform mat4 mv;\n"+
				"uniform mat4 p;\n"+
				"void main() {\n"+
				"	color = in_color;\n"+
				"	gl_Position = p * mv * in_position;\n"+
				"}\n";
			
			string fss =
				"#version 130\n"+
				"in vec3 color;\n"+
				"out vec4 out_color;\n"+
				"void main() {\n"+
				"	out_color = vec4(color, 1.0);\n"+
				"}\n";
		
			m_shader.LoadFromString(vss, fss);
			
			Screen scr = new Screen("TitleMenu");
		}
		
		protected void PrintLog(string desc, int shader)
		{
			string log = "";
			desc += " Log:\n";
			if (GL.IsShader(shader))
				log += GL.GetShaderInfoLog(shader);
			else if (GL.IsProgram(shader))
				log += GL.GetProgramInfoLog(shader);
			
			if (log.Length > 0)
				Console.WriteLine(log);
		}
		
		protected override void OnResize(EventArgs e)
		{
			base.OnResize(e);

			GL.Viewport(ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width, ClientRectangle.Height);

			Matrix4 projection = Matrix4.CreatePerspectiveFieldOfView((float)Math.PI / 4, Width / (float)Height, 1.0f, 64.0f);

			m_shader.UniformMatrix4("p", ref projection);
		}
		
		protected override void OnUpdateFrame (FrameEventArgs e)
		{
			base.OnUpdateFrame (e);

			foreach(Entity ent in m_objects) {
				ent.Update( e );
			}

			if (Keyboard[Key.Escape])
				Exit();

		}
		
		protected override void OnRenderFrame (FrameEventArgs e)
		{
			base.OnRenderFrame (e);
			
			GL.Clear (ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
			
			Matrix4 modelview = Matrix4.LookAt (Vector3.Zero, Vector3.UnitZ, Vector3.UnitY);
			
			m_shader.Bind ();
			m_shader.UniformMatrix4 ("mv", ref modelview);

			foreach (Quad ent in m_objects) {
				ent.Draw(e);
			}
			
			ErrorCode err = GL.GetError();
			if (err != ErrorCode.NoError)
			{
				Console.WriteLine("\nboom\n");
			}
			
			SwapBuffers();
		}
		
		[STAThread]
		static void Main()
		{
			// The 'using' idiom guarantees proper resource cleanup.
			// We request 30 UpdateFrame events per second, and unlimited
			// RenderFrame events (as fast as the computer can handle).
			using (Game game = new Game(1280, 720))
			{
				game.Run(60.0);
			}
		}
	}
}

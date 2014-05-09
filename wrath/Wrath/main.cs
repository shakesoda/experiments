using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Input;

namespace Wrath
{
	class Game : GameWindow
	{
		Sprite Arrow;

		public Game(int width, int height) :
			base(
				width, height,
				GraphicsMode.Default, "...", 0,
				DisplayDevice.Default, 3, 0,
				GraphicsContextFlags.Default
			)
		{
			SwapBuffers();
		}

		protected override void OnLoad(System.EventArgs e)
		{
			VSync = VSyncMode.On;
			GL.ClearColor(Color4.SlateGray);

			GL.Enable(EnableCap.Texture2D);
			GL.Enable(EnableCap.Blend);  
			GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);  

			Arrow = new Sprite();
			Arrow.Load("../assets/a.png");
			Arrow.SetPosition(new Vector3(130f,130f,0f));

			GL.LoadIdentity();
			GL.Ortho(0, this.Width, this.Height, 0, -1, 1);

		}
		
		protected override void OnUpdateFrame(FrameEventArgs e)
		{
			// This Update() has been passed down for GENERATIONS
			base.OnUpdateFrame(e);
			Console.WriteLine( e.Time );
			if (Keyboard[Key.Escape])
				Exit();
		}

		protected override void OnRenderFrame (FrameEventArgs e)
		{
			GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

			GL.MatrixMode(MatrixMode.Modelview);
			GL.LoadIdentity();

			// todo: use quad.cs, that stuff isn't total junk!
			Arrow.Render();

			GL.Flush(); // implicit on some platforms, but whatever.
			SwapBuffers();
		}
		
		static void Main(string[] args)
		{
			Game g = new Game(1280, 720);
			g.Run();
		}
	}
}

using System;
using System.Collections.Generic;

using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace Wrath
{
	public class Shader
	{
		public int vs;
		public int fs;
		public int program;
		
		/*
		public bool LoadFromFile(string vs, string fs)
		{
			string vss = "";
			string fss = "";
			return LoadFromString(vss, fss);
		}
		*/
		
		public bool LoadFromString(string vss, string fss)
		{
			program = GL.CreateProgram();

			vs = GL.CreateShader(ShaderType.VertexShader);
			fs = GL.CreateShader(ShaderType.FragmentShader);

			GL.ShaderSource(vs, vss);
			GL.ShaderSource(fs, fss);

			GL.CompileShader(vs);
			GL.CompileShader(fs);

			GL.AttachShader(program, vs);
			GL.AttachShader(program, fs);
			
			GL.BindAttribLocation(program, 0, "in_position");
			GL.BindAttribLocation(program, 1, "in_color");
			GL.BindFragDataLocation(program, 0, "out_color");
			GL.LinkProgram(program);
			GL.UseProgram(program);
			
			if (!PrintLog("Vertex Shader", vs) ||
			    !PrintLog("Fragment Shader", fs) ||
			    !PrintLog("Shader Program", program)
			    )
			{
				return false;
			}
			return true;
		}
		
		protected bool PrintLog(string desc, int shader)
		{
			string log = "";
			desc += " Log:\n";
			if (GL.IsShader(shader))
				log += GL.GetShaderInfoLog(shader);
			else if (GL.IsProgram(shader))
				log += GL.GetProgramInfoLog(shader);
			
			if (log.Length > 0)
			{
				Console.WriteLine(log);
				return false;
			}
			return true;
		}
		
		public void Bind()
		{
			GL.UseProgram(program);
		}
		
		// TONS of duping below:
		public void UniformInt(string name, ref int val)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.Uniform1(loc, val);
		}
		
		public void UniformFloat(string name, ref float val)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.Uniform1(loc, val);
		}
		
		public void UniformVector2(string name, ref Vector2 vec)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.Uniform2(loc, ref vec);
		}
		
		public void UniformVector3(string name, ref Vector3 vec)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.Uniform3(loc, ref vec);
		}
		
		public void UniformVector4(string name, ref Vector4 vec)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.Uniform4(loc, ref vec);
		}
		
		public void UniformMatrix4(string name, ref Matrix4 matrix)
		{
			int loc = GL.GetUniformLocation(program, name);
			GL.UniformMatrix4(loc, false, ref matrix);
		}
	}
}


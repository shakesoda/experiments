using System;
using System.Collections.Generic;
using OpenTK;
using OpenTK.Graphics;

namespace Wrath
{
	public class Screen
	{
		protected static Dictionary<string, Screen> screens;
		protected Stack<Entity> m_actors;

		public Screen(string name)
		{
			if (screens == null)
				screens = new Dictionary<string, Screen>();
			
			if (screens.ContainsKey(name))
				Console.WriteLine("WARNING: Screen name collision! Overwriting.");

			screens[name] = this;

			m_actors = new Stack<Entity>();

			Console.WriteLine("Created screen \""+name+"\"");
		}
				
		public virtual void Update(FrameEventArgs e)
		{
			Entity[] actors = m_actors.ToArray();
			for (int i = 0; i < actors.Length; i++)
			{
				actors[i].Update(e);
			}
		}
		
		public virtual void Draw()
		{
			
		}
	}
}


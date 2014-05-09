using System;

using OpenTK;
using OpenTK.Graphics;

namespace Wrath
{
	public class Entity
	{
		public Entity() {}
		
		public virtual void Initialize() {}
		public virtual void Update(FrameEventArgs e) {}
		public virtual void Draw(FrameEventArgs e) {}
		
		public double DistanceFrom(Entity e)
		{
			return (e.GetPosition() - m_position).Length;
		}
		
		public Vector3 DirectionFrom(Entity e)
		{
			Vector3 tmp = e.GetPosition() - m_position;
			tmp.Normalize();
			return tmp;
		}
		
		public void SetPosition(Vector3 pos) { m_position = pos; }
		public void SetRotation(Vector3 rot) { m_rotation = rot; }
		public void SetScale(Vector3 scale) { m_scale = scale; }
		
		public Vector3 GetPosition() { return m_position; }
		public Vector3 GetRotation() { return m_rotation; }
		public Vector3 GetScale() { return m_scale; }
		
		protected Vector3 m_position, m_rotation, m_scale;
		protected Matrix4 m_matrix;
	}
}
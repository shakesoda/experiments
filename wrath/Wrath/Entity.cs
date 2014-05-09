using OpenTK;

namespace Wrath
{
	public class Entity
	{
		protected Vector3 m_position, m_rotation, m_scale;
		protected Box2 m_bounds = new Box2(0f,0f,1f,1f);
		protected Matrix4 m_matrix;
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
		public void SetBounds(Box2 bound) { m_bounds = bound; }

		public Vector3 GetPosition() { return m_position; }
		public Vector3 GetRotation() { return m_rotation; }
		public Vector3 GetScale() { return m_scale; }
		public Box2 GetBounds() { return m_bounds; }
	}
}

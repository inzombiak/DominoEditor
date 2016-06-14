#pragma once

class Object;
class IComponent
{
public:
	IComponent()
	{
		m_owner = 0;
		m_inUse = true;
	};
	virtual ~IComponent() {} ;

	virtual void Update(float dt) {};

	void SetOwner(Object* owner)
	{
		m_owner = owner;
	};

	void SetInUse(bool inUse)
	{
		m_inUse = inUse;
	}
	bool GetInUse()
	{
		return m_inUse;
	}

	Object* GetOwner() const { return m_owner;  };
	virtual const char* GetName() = 0;
	virtual unsigned int GetID() { return m_id; }
	//virtual unsigned int GetID() { return GetIDFromName(GetName()); }
	//static unsigned int GetIDFromName(const char* name)
	//{
	//	return reinterpret_cast<ComponentID>(HashedString::hash_name(name));
	//}

protected:
	Object* m_owner;
	bool m_inUse;
	unsigned int m_id;
};


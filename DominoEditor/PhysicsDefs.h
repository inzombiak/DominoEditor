#pragma once

#include <array>
#include <vector>

#include "GameDefs.h"
#include "btBulletDynamicsCommon.h"

class Object;
namespace PhysicsDefs
{
	enum PhysicsEntityTypes
	{
		Box,
		Sphere,
		Compound,
		Constraint,
	};

	enum PhysicsBodyType
	{
		RigidBody,
		CompoundBody,
		NULLBody,
	};

	class ICreationData
	{
	public:
		virtual ~ICreationData() {};

		PhysicsEntityTypes GetShape()
		{
			return shapeType;
		}

		PhysicsBodyType GetBody()
		{
			return bodyType;
		}

		int id;
		Object* owner = 0;
		virtual ICreationData* clone() const = 0;
	protected:
		virtual void SetBodyAndShape() {};
		PhysicsEntityTypes shapeType;
		PhysicsBodyType bodyType;

	};

	class IRigidBodyCreationData : public ICreationData
	{
	public:
		virtual ~IRigidBodyCreationData() {};

		double mass;
		double friction;
		double rollingFriction;
		std::array<double, 3> rotationAngles;
		std::array<double, 3> msPosition;
	};

	class BoxCreationData : public IRigidBodyCreationData
	{
	public:
		BoxCreationData()
		{
			SetBodyAndShape();
		}

		virtual ~BoxCreationData() {};
		std::array<double, 3> boxDimensions;
	
		BoxCreationData* clone() const
		{
			return new BoxCreationData(*this);
		}

	protected:
		void SetBodyAndShape() override
		{
			ICreationData::shapeType = PhysicsEntityTypes::Box;
			ICreationData::bodyType = PhysicsBodyType::RigidBody;
		}
	};
	class SphereCreationData : public IRigidBodyCreationData
	{
	public:
		SphereCreationData()
		{
			SetBodyAndShape();
		}
		virtual ~SphereCreationData() {};
		double sphereRadius;

		SphereCreationData* clone() const
		{
			return new SphereCreationData(*this);
		}

	protected:
		void SetBodyAndShape() override
		{
			ICreationData::shapeType = PhysicsEntityTypes::Sphere;
			ICreationData::bodyType = PhysicsBodyType::RigidBody;
		}
	};

	class CompoundCreationData : public IRigidBodyCreationData
	{
	public:
		CompoundCreationData()
		{
			SetBodyAndShape();
		}
		virtual ~CompoundCreationData() 
		{
			for (int i = 0; i < rigidBodies.size(); ++i)
			{
				delete rigidBodies[i];
			}
		};

		std::vector<IRigidBodyCreationData*> rigidBodies;
		std::vector<btTransform> shapePositions;

		CompoundCreationData* clone() const
		{
			return new CompoundCreationData(*this);
		}
	protected:
		void SetBodyAndShape() override
		{
			ICreationData::shapeType = PhysicsEntityTypes::Compound;
			ICreationData::bodyType = PhysicsBodyType::CompoundBody;
		}
	};

	class ConstraintCreationData : public ICreationData
	{
	public:
		virtual ~ConstraintCreationData() {};
		Object* body1 = 0;
		Object* body2 = 0;
		btVector3 anchor;
		btVector3 upperAngularLimit;
		btVector3 lowerAngularLimit;
		btVector3 upperLinearLimit;
		btVector3 lowerLinearLimit;

		ConstraintCreationData* clone() const
		{
			return new ConstraintCreationData(*this);
		}

	protected:
		void SetBodyAndShape() override
		{
			ICreationData::shapeType = PhysicsEntityTypes::Constraint;
			ICreationData::bodyType = PhysicsBodyType::NULLBody;
		}
	};
}


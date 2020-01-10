

#include "LinearMath/btTransform.h"
#include "BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"

class  btCustomMaterial{
	// Custom material class. If attached as userpointer to a CollisionObject (body), it makes possible to modify the contact point behaviour
public:

	btVector3 	m_lateralFrictionDir1; //Lateral friction 1
	btScalar	m_contactMotion1;  //Motion speed for lateral friction 1
	int	m_useCounter1;
	int	m_useCounter2;

	btCustomMaterial()
	{
		m_lateralFrictionDir1.setValue(0.f,0.f,0.f);
		m_contactMotion1 = 0.f;
		m_useCounter1 = 0;
		m_useCounter2 = 0;
	}

	void setMotionSpeed (btScalar speed)
	{
		m_contactMotion1 = speed;
	}

	void setMotion (btVector3& direction, btScalar speed)
	{
		m_lateralFrictionDir1 = direction;
		m_contactMotion1 = speed;
	}
	
	int getUse1()
	{
		return m_useCounter1;
	}
	
	int getUse2()
	{
		return m_useCounter2;
	}

};

static bool CustomMaterialCombinerCallback(btManifoldPoint& cp, void* body0, void* body1)
{
	// Find material to modify cp
	btCustomMaterial* material = NULL;
	// object with custom material
	const btCollisionObject* obj;

	// Check if Object 0 has custom material (Usually this is executed)
	obj = (btCollisionObject*) body0;
	material = (btCustomMaterial*) obj->getUserPointer();
	if (material != NULL)
	{
		// Motion Friction Speed
		cp.m_contactPointFlags |= BT_CONTACT_FLAG_LATERAL_FRICTION_INITIALIZED;
		// Motion Friction Direction
		cp.m_lateralFrictionDir1 = quatRotate(obj->getWorldTransform().getRotation(), material->m_lateralFrictionDir1);
		cp.m_contactMotion1 = - material->m_contactMotion1;
		cp.m_lateralFrictionDir2 = cp.m_lateralFrictionDir1.cross(cp.m_normalWorldOnB);
		material->m_useCounter1 ++;
		return true;
	}
	
	// If not, has Object 1 custom material?
	obj = (btCollisionObject*) body1;
	material = (btCustomMaterial*) obj->getUserPointer();
	if (material != NULL)
	{
		cp.m_contactPointFlags |= BT_CONTACT_FLAG_LATERAL_FRICTION_INITIALIZED;
		// Motion Friction Direction
		cp.m_lateralFrictionDir1 = quatRotate(obj->getWorldTransform().getRotation(), material->m_lateralFrictionDir1);
		cp.m_contactMotion1 = material->m_contactMotion1;
		cp.m_lateralFrictionDir2 = cp.m_lateralFrictionDir1.cross(cp.m_normalWorldOnB); //is it ok?
		material->m_useCounter2 ++;
		return true;
	}
    return false;
}

/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkLogicManager_h_
#define _gkLogicManager_h_

#include "gkCommon.h"
#include "gkMathUtils.h"
#include "OgreSingleton.h"


// base types
class gkLogicBrick;
class gkLogicSensor;
class gkLogicController;
class gkLogicActuator;
class gkLogicLink;
class gkAbstractDispatcher;



enum gkDispatchedTypes
{
    DIS_CONSTANT=0,
    DIS_MOUSE,
    DIS_COLLISION,
    DIS_MAX,
};



// Manager for all logic brick related items.
class gkLogicManager : public Ogre::Singleton<gkLogicManager>
{
public:

    typedef utListClass<gkLogicLink> Links;
    typedef gkAbstractDispatcher* gkAbstractDispatcherPtr;

    typedef utStack<gkLogicSensor*>         SensorStack;
    typedef utStack<gkLogicActuator*>       ActuatorStack;

protected:

    Links m_links;

    gkAbstractDispatcherPtr*    m_dispatchers;
    SensorStack                 m_sensorStack;
    ActuatorStack               m_actuatorStack;

public:

    gkLogicManager();
    ~gkLogicManager();

    gkLogicLink *createLink(void);


    // Free links & reset dispatchers
    void clear(void);

    // Process updates 
    void update(gkScalar delta);

    // Get enumerated dispatcher  
    GK_INLINE gkAbstractDispatcher& getDispatcher(int dt) 
    { GK_ASSERT(m_dispatchers && dt >= 0 && dt <= DIS_MAX); return *m_dispatchers[dt]; }


    GK_INLINE void push(gkLogicSensor *v)       {GK_ASSERT(v); m_sensorStack.push(v);}
    GK_INLINE void push(gkLogicActuator *v)     {GK_ASSERT(v); m_actuatorStack.push(v);}

    static gkLogicManager& getSingleton(void);
    static gkLogicManager* getSingletonPtr(void);
};


#endif//_gkLogicManager_h_
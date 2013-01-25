#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils/matrix.h"
#include "Engine/Display/VoxelVolume.h"
#include "utils/Stats.h"
#include "utils/vec4.h"
#include <string.h>
#include "Engine/Display/Object3D.h"
#include "Actors/Spaceship.h"
#include "Engine/Render/GLRenderer.h"
#include "Engine/Scene/Scene3D.h"
#include "utils/UtilsDefines.h"
#include "Actors/Bullet.h"
#include "Actors/Asteroid.h"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

GLuint gProgram;

float uiWidth = 0.0f; float uiHeight = 0.0f;
static Stats stats;
ActorBase** pActors;

static const char *gVertexShader = NULL;
static const char *gFragmentShader  = NULL;
static const char *gSzShipRawData  = NULL;
static const char *gSzBulletRawData  = NULL;
static const char *gSzAsteroidData  = NULL;

timespec* gLastClock;
unsigned long int gLastTS = 0;

bool bIsSceneBuilt = false;
bool setupGraphics(int w, int h) {
	GLRenderer::GetInstance()->Init(w, h, gVertexShader, gFragmentShader);

	if(!bIsSceneBuilt)
	{
		pActors = new ActorBase*[128];

		pActors[0] = new Spaceship();
		pActors[0]->Load(gSzShipRawData);
		pActors[0]->SetAngleY(180);

		int i;
		for(i = 1; i < 128; i++)
		{
			pActors[i] = NULL;
		}

		Scene3D::GetInstance()->SetCameraX(0.0);
		Scene3D::GetInstance()->SetCameraY(150.0);
		Scene3D::GetInstance()->SetCameraZ(30.0f);

		Scene3D::GetInstance()->SetFocusX(0.0f);
		Scene3D::GetInstance()->SetFocusY(0.0f);
		Scene3D::GetInstance()->SetFocusZ(-75.0f);

//		Scene3D::GetInstance()->SetCameraX(0.0);
//		Scene3D::GetInstance()->SetCameraY(50.0);
//		Scene3D::GetInstance()->SetCameraZ(1.0f);
//
//		Scene3D::GetInstance()->SetFocusX(0.0f);
//		Scene3D::GetInstance()->SetFocusY(0.0f);
//		Scene3D::GetInstance()->SetFocusZ(0.0f);


		Scene3D::GetInstance()->SetLightX(0.0f);
		Scene3D::GetInstance()->SetLightY(20.0f);
		Scene3D::GetInstance()->SetLightZ(0.0f);
		bIsSceneBuilt = true;
	}

    return true;
}

void AddAsteroid(int nLaneID)
{
	float LANE_POS_X[] = {-30.0f, 0.0f, 30.0f};
	if(pActors != NULL)
	{
		for(int i = 0; i < 128; i++)
		{
			//finds an empty spot for creating the bullet
			if(pActors[i] == NULL)
			{
				pActors[i] = new Asteroid();
				pActors[i]->Load(gSzAsteroidData);
				pActors[i]->SetPositionX(LANE_POS_X[nLaneID]);
				pActors[i]->SetPositionY(pActors[0]->GetPositionY());
				pActors[i]->SetPositionZ(pActors[0]->GetPositionZ() - 300);
				return;
			}
		}
	}
}

int counter = 0;
void Step() {
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	int i,j;

	float fActorDistanceSquared;
	float fActorDistanceX, fActorDistanceY, fActorDistanceZ;

	int nStepMs = now.tv_sec * 1000 + now.tv_nsec / 1000000 - gLastTS;
	gLastTS = now.tv_sec * 1000 + now.tv_nsec / 1000000;
	if(pActors != NULL)
	{
		GLRenderer::GetInstance()->PreRender();


		for(i = 0; i < 128; i++)
		{
			if(pActors[i] != NULL)
			{
				//checks for collisions with every other blocks
				for(j = 0; j < 128; j++)
				{
					if(pActors[j] != NULL && j != i)
					{
						fActorDistanceX = pActors[i]->GetPositionX() - pActors[j]->GetPositionX();
						fActorDistanceY = pActors[i]->GetPositionY() - pActors[j]->GetPositionY();
						fActorDistanceZ = pActors[i]->GetPositionZ() - pActors[j]->GetPositionZ();

						fActorDistanceSquared = fActorDistanceX * fActorDistanceX + fActorDistanceY * fActorDistanceY + fActorDistanceZ * fActorDistanceZ;

						if(fActorDistanceSquared < (pActors[i]->GetBoundingRadius() + pActors[j]->GetBoundingRadius()) * (pActors[i]->GetBoundingRadius() + pActors[j]->GetBoundingRadius()))
						{
							pActors[i]->ProcessCollisionWith(pActors[j]);
							pActors[j]->ProcessCollisionWith(pActors[i]);
							break;
						}
					}
				}

				pActors[i]->Update(nStepMs);
				pActors[i]->Render(gProgram, uiWidth, uiHeight);
			}
		}

		for(i = 0; i < 128; i++)
		{
			if(pActors[i] != NULL)
			{
				if(pActors[i]->GetExpired() == true)
				{
					SAFE_DELETE(pActors[i]);
				}
			}
		}
	}

	counter++;

	if(counter == 64)
	{
		counter = 0;
		AddAsteroid(floor((double)rand() / (double)RAND_MAX * 3.0f));
	}
}

void FireBullet()
{
	if(pActors != NULL)
	{
		for(int i = 0; i < 128; i++)
		{
			//finds an empty spot for creating the bullet
			if(pActors[i] == NULL)
			{
				pActors[i] = new Bullet();
				pActors[i]->Load(gSzAsteroidData);
				pActors[i]->SetPositionX(pActors[0]->GetPositionX() + 1.0f);
				pActors[i]->SetPositionY(pActors[0]->GetPositionY() + 0.0f);
				pActors[i]->SetPositionZ(pActors[0]->GetPositionZ() - 9.0f);
				return;
			}
		}
	}
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring vShader, jstring fShader, jstring shipRawData, jstring bulletRawData, jstring asteroidRawData);
    JNIEXPORT void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_HandleMouseInput(JNIEnv * env, jobject obj, jint inputType);
};

JNIEXPORT void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring vShader, jstring fShader, jstring shipRawData, jstring bulletRawData, jstring asteroidRawData)
{
    if(!gVertexShader && !gFragmentShader) {
		gVertexShader = env->GetStringUTFChars(vShader, 0);
		gFragmentShader = env->GetStringUTFChars(fShader, 0);
		gSzShipRawData = env->GetStringUTFChars(shipRawData, 0);
		gSzBulletRawData = env->GetStringUTFChars(bulletRawData, 0);
		gSzAsteroidData = env->GetStringUTFChars(asteroidRawData, 0);
    }
	setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_step(JNIEnv * env, jobject obj)
{
//	clock_getres(CLOCK_REALTIME, gLastClock);
	Step();

//	LOGI("render duration: %d", gLastClock->tv_nsec - gLastTS);

//	gLastTS = gLastClock->tv_nsec;
}

void JNICALL Java_com_kittensoft_nativevoxelprototype_NativeVoxelPrototypeLib_HandleMouseInput(JNIEnv * env, jobject obj, jint inputType) {
	if(inputType == SWIPE_LEFT)
	{
		((Spaceship*)pActors[0])->MoveLeft();
	}

	if(inputType == SWIPE_RIGHT)
	{
		((Spaceship*)pActors[0])->MoveRight();
	}

	if(inputType == DOUBLE_TAP)
	{
		FireBullet();
	}
}

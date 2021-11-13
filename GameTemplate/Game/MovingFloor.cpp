#include "stdafx.h"
#include "MovingFloor.h"

#include "Player.h"

namespace
{
	Vector3	SCALE = Vector3(3.0f, 1.0, 3.0f);
	float SPEED = 200.0f;
	float LIMITED = 300.0f;
}

MovingFloor::MovingFloor()
{

}

MovingFloor::~MovingFloor()
{

}

bool MovingFloor::Start()
{
	m_modelRender.Init("Assets/modelData/sample/box.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	m_firstPosition = m_position;
	m_spriteRender.Init("Assets/sprite/arrow.dds",70,70);
	return true;
}

void MovingFloor::Update()
{
	Move();

	m_modelRender.Update();
}

void MovingFloor::Move()
{

	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.x = -SPEED;
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.x = SPEED;
	}

	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.x - LIMITED >= m_position.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.x + LIMITED <= m_position.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingRight;
		}
	}

	m_modelRender.SetPosition(m_position);

	
	Vector3 position = m_position;
	//オブジェクトの上の方に画像を表示したいので。
	//y座標を少し大きくする。
	position.y += 130.0f;
	//ワールド座標からスクリーン座標を計算。
	//計算結果がm_spritePositionに代入される。
	g_camera3D->CalcScreenPositionFromWorldPosition(m_spritePosition, position);
	m_spriteRender.SetPosition(Vector3(m_spritePosition.x,m_spritePosition.y,0.0f));
	m_spriteRender.Update();
}

void MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
}
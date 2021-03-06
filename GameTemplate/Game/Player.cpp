#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_characterController.Init(20.0f,
		100.0f,
		m_position);
	return true;
}

void Player::Update()
{
	Move();

	m_modelRender.Update();
}

void Player::Move()
{
	//このフレームの移動量を求める。
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed += cameraForward * lStick_y * 500.0f;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * lStick_x * 500.0f;		//右方向への移動速度を加算。

	if (g_pad[0]->IsTrigger(enButtonA) //Aボタンが押されたら
		&& m_characterController.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_moveSpeed.y = 400.0f;	//上方向に速度を設定して、
	}

	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//キャラクターコントローラーを使用して、座標を更新。

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_characterController.IsOnGround()) {
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}

	//座標を設定。
	m_modelRender.SetPosition(m_position);

	//ここで0にする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
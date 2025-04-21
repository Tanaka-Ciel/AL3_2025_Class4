#include "Gamescene.h"

using namespace KamataEngine;

// デストラクタ
Gamescene::~Gamescene() { 
	delete sprite_;
	delete model_;
}

void Gamescene::Initialize() { 
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("debugfont.png"); 

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//3Dモデルの生成
	model_ = Model::Create();
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();

}

void Gamescene::Update() {

	Vector2 position = sprite_->GetPosition();

	position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);
}

void Gamescene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	Sprite::PostDraw();



	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, camera_, textureHandle_);

	Model::PostDraw();
}
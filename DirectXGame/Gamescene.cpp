#include "Gamescene.h"

using namespace KamataEngine;

Gamescene::~Gamescene() { 
	delete model_;
}

void Gamescene::Initialize() { 
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario_PNG125.png"); 

	//3Dモデルの生成
	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();

	//delete model_;
}

void Gamescene::Update() {

}

void Gamescene::Draw() {
	//DirectXCommonのインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	//3Dモデル描画
	model_->Draw(worldTransform_, camera_, textureHandle_);


	//3Dモデル描画処理
	Model::PostDraw();

}
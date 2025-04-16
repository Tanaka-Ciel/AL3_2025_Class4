#include "Gamescene.h"

using namespace KamataEngine;

// デストラクタ
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

}

void Gamescene::Update() {

}

void Gamescene::Draw() {

}
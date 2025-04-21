#pragma once
#include "KamataEngine.h"
#include "Player.h"



//ゲームシーン
class Gamescene 
{

	uint32_t textureHandle_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	Player* player_ = nullptr;

	public:

		~Gamescene();

		//初期化
	    void Initialize();

		//更新
	    void Update();

		//描画
	    void Draw();
};

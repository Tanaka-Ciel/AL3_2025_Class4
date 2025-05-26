#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>



//ゲームシーン
class Gamescene 
{
public:

	KamataEngine::WorldTransform worldTransform;
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelplayer_ = nullptr;
	KamataEngine::Camera camera_;
	KamataEngine::Model* modelSkydome_ = nullptr;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

		//初期化
	    void Initialize();

		//更新
	    void Update();

		//描画
	    void Draw();

		~Gamescene();

		//デバッグカメラ有効
	    bool isDebugCameraActive_ = false;

		//デバッグカメラ
	    KamataEngine::DebugCamera* debugCamera_ = nullptr;


private:

		uint32_t textureHandle_ = 0;

};

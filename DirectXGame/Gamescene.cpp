#include "Gamescene.h"
#include "Mymath.h"

using namespace KamataEngine;

// デストラクタ
Gamescene::~Gamescene() { 
	delete sprite_;
	delete model_;
	delete player_;
	delete debugCamera_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void Gamescene::Initialize() { 
	//ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("debugfont.png"); 

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//3Dモデルの生成
	model_ = Model::CreateFromOBJ("cube");

	//カメラの初期化
	camera_.Initialize();

	//自キャラの生成
	player_ = new Player();

	//自キャラの初期化
	player_->Initialize(model_, textureHandle_, &camera_);

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック一個分の横幅
	const float kBlockHeight = 2.0f;
	const float kBlockWidth = 2.0f;
	//要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);
	worldTransformBlocks_.resize(kNumBlockHorizontal);

	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if ((i + j) % 2 == 0)
				continue;
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}
	}

}

void Gamescene::Update() {
	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)){
		isDebugCameraActive_=!isDebugCameraActive_;
	}
	#endif

	Vector2 position = sprite_->GetPosition();

	if (isDebugCameraActive_) 
	{
		// デバッグカメラの更新
		debugCamera_->Update();
		// デバッグカメラのビュー行列
		camera_.matView = camera_.matView = debugCamera_->GetCamera().matView;
		// デバッグカメラのプロジェクション行列
		camera_.matProjection = camera_.matProjection = debugCamera_->GetCamera().matProjection;
		//ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

	position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);
	player_->Update();

	//ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
		}
	}
}

void Gamescene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	Sprite::PostDraw();



	Model::PreDraw(dxCommon->GetCommandList());

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			model_->Draw(*worldTransformBlock, camera_);
		}
	}

	player_->Draw();

	Model::PostDraw();

	
}
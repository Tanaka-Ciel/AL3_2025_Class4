#include "KamataEngine.h"
#include "Skydome.h"

using namespace KamataEngine;

void Skydome::Initialize(Model* model, uint32_t textureHandle, Camera* camera) {
	assert(model);
	camera_ = camera;
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.TransferMatrix(); }

void Skydome::Draw() { model_->Draw(worldTransform_, *camera_); }
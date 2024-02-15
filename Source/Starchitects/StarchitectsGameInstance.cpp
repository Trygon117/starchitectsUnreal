// Fill out your copyright notice in the Description page of Project Settings.


#include "StarchitectsGameInstance.h"
#include "WebSocketsModule.h"

void UStarchitectsGameInstance::Init() {
    Super::Init();

    if(!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://127.0.0.1:443");

    WebSocket->Connect();
}

void UStarchitectsGameInstance::Shutdown() {

    if(WebSocket->IsConnected()) {
        WebSocket->Close();
    }

    Super::Shutdown();
}
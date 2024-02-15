// Fill out your copyright notice in the Description page of Project Settings.


#include "StarchitectsGameInstance.h"
#include "WebSocketsModule.h"

void UStarchitectsGameInstance::Init() {
    Super::Init();

    if(!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://127.0.0.1:443");

    WebSocket->OnConnected().AddLambda([]() {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected");
    });

    WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
    });

    WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection Closed: " + Reason);
    });

    WebSocket->OnMessage().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Recieved Message: " + Message);
    });

    WebSocket->OnMessageSent().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent Message: " + Message);
    });

    WebSocket->Connect();
}

void UStarchitectsGameInstance::Shutdown() {

    if(WebSocket->IsConnected()) {
        WebSocket->Close();
    }

    Super::Shutdown();
}
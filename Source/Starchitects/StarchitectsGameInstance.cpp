// Fill out your copyright notice in the Description page of Project Settings.
// Youtube Tutorial for Websockets: https://www.youtube.com/watch?v=l9TTmtDBTWY
// WebSockets Documentation: https://docs.unrealengine.com/4.27/en-US/API/Runtime/WebSockets/

#include "StarchitectsGameInstance.h"
#include "WebSocketsModule.h"
#include "Json.h"
#include "UObject/ConstructorHelpers.h"

void UStarchitectsGameInstance::Init()
{
    Super::Init();

    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    const FString ServerURL = TEXT("ws://127.0.0.1:3000/"); // Your server URL. You can use ws, wss or wss+insecure.
    const FString ServerProtocol = TEXT("ws");              // The WebServer protocol you want to use.

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

    WebSocket->OnConnected().AddLambda([&]() {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected");
        WebSocket->Send("{\"header\":0, \"data\":{}}");
    });

    WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
    });

    WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection Closed: " + Reason);
    });

    WebSocket->OnMessage().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Recieved Message: " + Message);
        UE_LOG(LogTemp, Warning, TEXT("Recieved Message: \"%s\"."), *Message);
    });

    WebSocket->OnRawMessage().AddLambda([](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) {
        // This code will run when we receive a raw (binary) message from the server.
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, "Recieved Raw Message");
        UE_LOG(LogTemp, Warning, TEXT("Recieved Raw Message"));
    });

    WebSocket->OnMessageSent().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent Message: " + Message);
    });

    // if (GEngine)
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hello!"));

    // example send message
    // WebSocket->Send("Test Message");

    WebSocket->Connect();

    // AddStarDebug();

    FStarData testData;

    testData.name = "This Is A Test";

    AStarObj* newStar = GetWorld()->SpawnActor<AStarObj>(AStarObj::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    newStar->SetUpData(testData);
    // newStar->SetActorRelativeScale3D(FVector::OneVector);
}

void UStarchitectsGameInstance::Shutdown()
{

    if (WebSocket->IsConnected())
    {
        WebSocket->Close();
    }

    Super::Shutdown();
}

void UStarchitectsGameInstance::LoadStars(FString json)
{

    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);

    // return if json is not parseable

    // for each json in the web socket
    // FStarData data
    // get each data from the array and add it to the map
}

void UStarchitectsGameInstance::AddStar()
{
}

void UStarchitectsGameInstance::AddStarDebug()
{
    // static ConstructorHelpers::FClassFinder<AActor> StarClassFinder(TEXT("/Game/Star"));
    // bool doesItExit = StarClassFinder.Class == NULL;
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, doesItExit ? "False" : "True");

    // StarClass = StarClassFinder.Class;

    // AActor* newStar = GetWorld()->SpawnActor<AActor>(StarClass, FVector::ZeroVector, FRotator::ZeroRotator);

    AStarObj* newStar = GetWorld()->SpawnActor<AStarObj>(AStarObj::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
}

// Reads the value of a given field in a stringified JSON Object
// FString UStarchitectsGameInstance::ParseJSON(FString json, FString field)
// {
//     TSharedPtr<FJsonObject> JsonParsed;
//     TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);
//     if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
//     {
//         return JsonParsed->GetStringField(field);
//     }
//     else
//     {
//         return "";
//     }
// }
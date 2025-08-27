#include <raylib.h>
#include <cmath>

Vector3 normaliseVector(Vector2 ball, Vector2 mouse);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 608;
    InitWindow(screenWidth, screenHeight, "vector game");
    SetTargetFPS(60);

    Vector2 ball = {screenWidth / 2,screenHeight / 2 };
    Vector2 mouse = {540,50};
    Vector3 lastNormVec = {0,0,0};
    Vector3 normalisedVector = {0,0,0};
    
    float speed = 0;
    float topSpeed = 5;
    float acceleration = 0.4;
    float friction = 0.09;

    while (!WindowShouldClose())
    {

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();

            normalisedVector = normaliseVector(ball, mouse);
            lastNormVec = normalisedVector;

            // Ball is able to reach max speed
            if (normalisedVector.z > 60){
                ball.x += normalisedVector.x * speed;
                ball.y += normalisedVector.y * speed;
				speed >= topSpeed ? speed = topSpeed : speed += acceleration;
            }
            // Slow ball down when closer
            else if(normalisedVector.z <= 60){
                int test = 62 - normalisedVector.z;
                if (normalisedVector.z > 0){
                    ball.x += normalisedVector.x * (speed / test);
                    ball.y += normalisedVector.y * (speed / test);
					speed >= topSpeed ? speed = topSpeed : speed;
                }
            }
    }
    else{
            normalisedVector = normaliseVector(ball, mouse); // just to get the magnitude
            ball.x += lastNormVec.x * speed;
            ball.y += lastNormVec.y * speed;
            
            speed >= 0.2 ? speed -= friction : speed = 0;
    }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("Mag: %.2f", normalisedVector.z), 10, 10, 20, BLACK);
            DrawCircle( (int)ball.x, (int)ball.y, 20, RED );

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

Vector3 normaliseVector(Vector2 ball, Vector2 mouse){

    float vectorX = mouse.x - ball.x;
    float vectorY = mouse.y - ball.y;

    float magnitude = sqrt(vectorX * vectorX + vectorY * vectorY);

    float threshold = 30; // Adjust this threshold as needed
    if (magnitude > threshold) {
        float normalisedVectorX = vectorX / magnitude;
        float normalisedVectorY = vectorY / magnitude;
        return { normalisedVectorX, normalisedVectorY, magnitude };
    } else {
        return (Vector3{0,0,magnitude});
    }
}
#include "Character.h"

Character::Character()
{
    posX = SCREEN_WIDTH - 700;
    posY = GROUND;

    status = 0;
    jumpsRemaining = 2; // số lần nhảy còn lại
}

bool Character::OnGround()
{
    return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            {
                if (jumpsRemaining > 0) // kiểm tra số lần nhảy còn lại
                {
                    Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                    status = JUMP;
                    jumpsRemaining--;
                }
                break;
            }
        }
    }
}

void Character::Move()
{
    // Nếu nhân vật đang trong trạng thái nhảy
    if (status == JUMP)
    {
        if (posY > MAX_HEIGHT) 
        {
            // Di chuyển lên trên
            posY -= JUMP_SPEED;
        }
        else
        {
            // Chuyển sang trạng thái rơi
            status = FALL;
        }
    }
    // Nếu nhân vật đang trong trạng thái rơi
    else if (status == FALL)
    {
        // Nếu nhân vật chưa đạt đất
        if (posY < GROUND)
        {
            // Di chuyển xuống dưới
            posY += FALL_SPEED;
        }
        // Nếu nhân vật đã đạt đất
        else
        {
            // Chuyển sang trạng thái chạy
            status = RUN;
            // Cập nhật lại số lần nhảy còn lại
            jumpsRemaining = 2;
        }
    }
}


void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
    gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
    return posX;
}

int Character::GetPosY()
{
    return posY;
}

#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(int x, int y, int width, int height, int nFrames, const Surface& sprite, Color chroma)
	:
	sprite(sprite),
	chroma(chroma)
{
	frames.reserve(nFrames);
	for (int i = 0; i < nFrames; i++)
	{
		frames.emplace_back(x + (i * width), x + ((i + 1) * width), y, y + height);
	}
}

void Animation::Draw(const Vec2I& pos, Graphics& gfx) const
{
	SpriteEffect::Chroma effect{ chroma };
	gfx.DrawSprite(pos.x, pos.y, frames[curFrame], sprite, effect);
}

void Animation::Draw(const Vec2I& pos, const RectI& clip, Graphics& gfx) const
{
	SpriteEffect::Chroma effect{ chroma };
	gfx.DrawSprite(pos.x, pos.y, frames[curFrame], clip, sprite, effect);
}

void Animation::Update(float dt)
{
	curFramTime += dt;
	while (curFramTime >= holdTime)
	{
		Advance();
		curFramTime -= holdTime;
	}
}

void Animation::Advance()
{
	curFrame++;
	if (curFrame >= frames.size())
	{
		curFrame = 0;
	}
}

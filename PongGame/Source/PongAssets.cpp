#include "ResInclude/BallescapesoundEmbed.h"
#include "ResInclude/BallhitsoundEmbed.h"
#include "ResInclude/IconEmbed.h"
#include "ResInclude/IconimageEmbed.h"
#include "ResInclude/ObliviousfontEmbed.h"
#include "ResInclude/PongmusicEmbed.h"

namespace PongAssets {
    unsigned char* GetBallescapesoundEmbedData()
    {
        return BallescapesoundEmbed::BallescapesoundEmbedData;
    }
    unsigned int GetBallescapesoundEmbedSize()
    {
        return BallescapesoundEmbed::BallescapesoundEmbedSize;
    }
    unsigned char* GetBallhitsoundEmbedData()
    {
        return BallhitsoundEmbed::BallhitsoundEmbedData;
    }
    unsigned int GetBallhitsoundEmbedSize()
    {
        return BallhitsoundEmbed::BallhitsoundEmbedSize;
    }
    unsigned char* GetIconEmbedData()
    {
        return IconEmbed::IconEmbedData;
    }
    unsigned int GetIconEmbedSize()
    {
        return IconEmbed::IconEmbedSize;
    }
    unsigned char* GetIconimageEmbedData()
    {
        return IconimageEmbed::IconimageEmbedData;
    }
    unsigned int GetIconimageEmbedSize()
    {
        return IconimageEmbed::IconimageEmbedSize;
    }
    unsigned char* GetObliviousfontEmbedData()
    {
        return ObliviousfontEmbed::ObliviousfontEmbedData;
    }
    unsigned int GetObliviousfontEmbedSize()
    {
        return ObliviousfontEmbed::ObliviousfontEmbedSize;
    }
    unsigned char* GetPongmusicEmbedData()
    {
        return PongmusicEmbed::PongmusicEmbedData;
    }
    unsigned int GetPongmusicEmbedSize()
    {
        return PongmusicEmbed::PongmusicEmbedSize;
    }
}
#include <SFML-utils/map-editor/TileInfo.hpp>

namespace sfutils
{
    namespace editor
    {
        TileInfo::TileInfo(int az,const sf::Vector2i& acoord):
            z(az),
            coord(acoord)
        {
        }


        bool TileInfo::operator<(const TileInfo& other)const
        {
            if(z == other.z)
            {
                if(coord.x == other.coord.x)
                {
                    return coord.y < other.coord.y;
                }
                return coord.x < other.coord.x;
            }
            return z < other.z;

        }

        bool TileInfo::operator==(const TileInfo& other)const
        {
            return (z == other.z) && (coord == other.coord);
        }
    }
}


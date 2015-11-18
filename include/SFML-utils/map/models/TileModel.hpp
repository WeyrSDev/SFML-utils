#ifndef SFUTILS_MAP_TILEMODEL_HPP
#define SFUTILS_MAP_TILEMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-utils/map/models/LayerModel.hpp>

namespace sfutils
{
    namespace map
    {
        class TileModel : public orm::SqlObject<TileModel>
        {
            public:
                TileModel();

                orm::CharField<255> texture;
                orm::CharField<255> textureFrame;
                orm::IntegerField x;
                orm::IntegerField y;
                orm::FK<LayerModel> layer;
                
                MAKE_STATIC_COLUMN(texture,textureFrame,x,y,layer);

            private:
        };
    }
}
#endif
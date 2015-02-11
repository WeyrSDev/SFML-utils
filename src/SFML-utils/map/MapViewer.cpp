#include <SFML-utils/map/MapViewer.hpp>

#include <SFML-utils/map/VMap.hpp>
#include <SFML-utils/map/Configuration.hpp>

namespace sfutils
{
    namespace map
    {        
        template <typename T>
        inline T clamp(T value, T min, T max)
        {
            return value < min ? min : (value > max ? max : value);
        }

        MapViewer::MapViewer(sf::RenderWindow& window,const VMap& map) : MapViewer(window,map,sfutils::map::Configuration::default_map_inputs)
        {
        }
        
        MapViewer::MapViewer(sf::RenderWindow& window,const VMap& map,const ActionMap<int>& action_map) : ActionTarget(action_map),_map(map), _zoom(1),_move_x(0), _move_y(0), _movement_speed(5), _window(window)
        {
            bind(Action(sf::Event::MouseWheelMoved),[this](const sf::Event& event){
                     zoom(1-(event.mouseWheel.delta/5.0));
                 });


            bind(Configuration::MapInputs::MoveUp,[this](const sf::Event& event){
                    
                    _move_y =clamp(_move_y-1,-1,1);
                 });

            bind(Configuration::MapInputs::MoveDown,[this](const sf::Event& event){
                    _move_y = clamp(_move_y+1,-1,1);
                 });

            bind(Configuration::MapInputs::MoveLeft,[this](const sf::Event& event){
                    _move_x = clamp(_move_x-1,-1,1);
                 });

            bind(Configuration::MapInputs::MoveRight,[this](const sf::Event& event){
                    _move_x = clamp(_move_x+1,-1,1);
                 });

            auto size = _window.getSize();
            setSize(size.x,size.y);
        }

        void MapViewer::move(float offsetX, float offsetY)
        {
            _view.move(offsetX,offsetY);
        }

        void MapViewer::move(const sf::Vector2f& offset)
        {
            _view.move(offset);
        }

        void MapViewer::setPosition(float posX, float posY)
        {
            _view.setCenter(posX,posY);
        }

        void MapViewer::setPosition(const sf::Vector2f& pos)
        {
            _view.setCenter(pos);
        }

        sf::Vector2f MapViewer::getPosition()const
        {
            return _view.getCenter();
        }

        void MapViewer::zoom(float factor)
        {
            _zoom *=factor;
            _view.zoom(factor);
        }

        float MapViewer::getZoom()const
        {
            return _zoom;
        }

        void MapViewer::setSize(float width,float height)
        {
            _view.setSize(width,height);
        }

        void MapViewer::setSize(const sf::Vector2f& size)
        {
            _view.setSize(size);
        }

        void MapViewer::update(float deltaTime)
        {
            if(_move_x or _move_y)
            {
                float delta = _map._tile_size*_movement_speed * deltaTime;
                move(_move_x * delta * _movement_speed,_move_y * delta * _movement_speed);
            }
            _move_x = 0;
            _move_y = 0;

        }
        void MapViewer::setSpeed(float speed)
        {
            _movement_speed = speed;
        }

        void MapViewer::draw(sf::RenderStates states) const
        {
            draw(_window,states);
        }

        sf::Vector2i MapViewer::mapScreenToCoords(int x,int y)const
        {
            sf::Vector2f pos = _window.mapPixelToCoords(sf::Vector2i(x,y),_view); 
            return _map.mapPixelToCoords(pos.x,pos.y);
        }

        sf::Vector2i MapViewer::mapScreenToCoords(const sf::Vector2i& pos)const
        {
            return mapScreenToCoords(pos.x,pos.y);
        }

        sf::Vector2i MapViewer::mapCoordsToScreen(int x,int y) const
        {
            sf::Vector2f pos = _map.mapCoordsToPixel(x,y);
            return _window.mapCoordsToPixel(sf::Vector2f(pos.x,pos.y),_view);
        }

        sf::Vector2i MapViewer::mapCoordsToScreen(const sf::Vector2i& pos) const
        {
            return mapCoordsToScreen(pos.x,pos.y);
        }

        sf::Vector2i MapViewer::mapPixelToCoords(float x,float y) const
        {
            return _map.mapPixelToCoords(x,y);
        }

        sf::Vector2i MapViewer::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            return _map.mapPixelToCoords(pos.x,pos.y);
        }

        sf::Vector2f MapViewer::mapCoordsToPixel(int x,int y) const
        {
            return _map.mapCoordsToPixel(x,y);
        }

        sf::Vector2f MapViewer::mapCoordsToPixel(const sf::Vector2i& pos) const
        {
            return _map.mapCoordsToPixel(pos.x,pos.y);
        }

        void MapViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            sf::View view = target.getView();
            target.setView(_view);

            _map.draw(target,states,sf::FloatRect(target.mapPixelToCoords(sf::Vector2i(0,0),_view),
                                                  _view.getSize()));
            target.setView(view);
        }
    }
}

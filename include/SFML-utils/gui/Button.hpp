#ifndef SFML_UTILS_GUI_BUTTON_HPP
#define SFML_UTILS_GUI_BUTTON_HPP

#include <utils/event/Emitter.hpp>

#include <SFML-utils/gui/Widget.hpp>
#include <SFML-utils/gui/event/ButtonPressed.hpp>
#include <SFML-utils/gui/event/ButtonReleased.hpp>


namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A class that represent a Button with events
         */ 
        class Button : virtual public Widget,
        protected utils::event::Emitter<event::ButtonPressed>, protected utils::event::Emitter<event::ButtonReleased> //disable call of emit from the outside
        {
            public:
                Button(const Button&) = delete;
                Button& operator=(const Button&) = delete;

                /**
                 * \brief constructor
                 */
                explicit Button(Widget* parent=nullptr);
                virtual ~Button();

                /**
                 * \brief use the connect function for event::ButtonPressed event
                 */
                using utils::event::Emitter<event::ButtonPressed>::connect;

                /**
                 * \brief use the disconnect function for event::ButtonPressed event
                 */
                using utils::event::Emitter<event::ButtonPressed>::disconnect;

                /**
                 * \brief use the connect function for event::ButtonReleased event
                 */
                using utils::event::Emitter<event::ButtonReleased>::connect;

                /**
                 * \brief use the disconnect function for event::ButtonReleased event
                 */
                using utils::event::Emitter<event::ButtonReleased>::disconnect;

                /**
                 * \brief remove all the connections
                 */
                void clearLambdas();

                /**
                 * \brief emit ButtonPressed and ButtonReleased event
                 */
                void click();

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;

                virtual void onMouseEntered();
                virtual void onMouseLeft();

            private:

                enum Status {
                    Hover = 1
                };
                int _status;
        };
    }
}
#endif

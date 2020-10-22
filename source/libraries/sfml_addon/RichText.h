#ifndef RICHTEXT_H 
#define RICHTEXT_H 

#include <SFML/Graphics.hpp>

namespace sf
{
	class RichText : public sf::Drawable, public Transformable
	{
	private:
		String              m_string;
		const Font*			m_font;
		unsigned int        m_characterSize;
		Uint32              m_style;
		Color               m_fillColor;
		Color               m_outlineColor;

	protected:
		void draw(RenderTarget& target, RenderStates states);

	public:
		RichText();
		RichText(const String& string, const Font& font, unsigned int characterSize = 30);

	};
}

#endif // RICHTEXT_H

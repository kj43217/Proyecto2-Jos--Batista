#include <SFML/Graphics.hpp>
#include "G-World.h"

using namespace std;
using namespace sf;
int main()
{
	//condicionales de estado
	bool standing = true;
	bool airborn = false;
	bool spacep = false;
	bool ap = false;
	bool dp = false;

	//crear parametros de la ventana.
	sf::RenderWindow window(sf::VideoMode(960, 560), "proyecto 1");

	//limitar el framerate
	window.setFramerateLimit(60);


	//crea eventos
	Event event;

	//crea el reloj que controla los frames
	Clock clock;

	//crear retenedores de texturas y sprites
	Texture PlayerTexture;
	Sprite PlayerSprite;
	Texture BG_Texture;
	Sprite BG_Sprite;

	//cargar texturas
	if (!BG_Texture.loadFromFile("assets/battle bg.png"))
	{
		//en caso de que no cargue se le avisa al usuario
		cout << "no se encontro la textura" << endl;
	}

	if (!PlayerTexture.loadFromFile("assets/Flame head idle (frame 1).gif"))
	{
		cout << "no se encontro la textura de jugador." << endl;
	}


	//asignar las texturas a los srites----------------
	PlayerSprite.setTexture(PlayerTexture);
	BG_Sprite.setTexture(BG_Texture);
	//-------------------------------------------------

	//le damos tamaño proporcional al de la ventana para que encaje.-------
	BG_Sprite.setScale(Vector2f(0.704845815f, 0.777777778f));
	PlayerSprite.setScale(Vector2f(0.50f, 0.50f));
	//---------------------------------------------------------------------

	//configracion del mundo y el cuerpo 

	World world;
	world.setGravity(Vec2(0.0f, 500.0f));

	Body b1;
	//asignar masa del objeto
	b1.mass = 5.0f;
	//valor de masa inversa
	b1.invMass = 1 / b1.mass;
	//asignar posicion en la ventana
	b1.position = Vec2(200.0f, 290.0f);
	//asignar velocidad inicial del objeto
	b1.velocity = Vec2(0.0f, 0.0f);


	//Agregar el cuerpo al mundo para que se afectado por sus propiedades------
	world.addBody(&b1);

	Rect<float> size = PlayerSprite.getGlobalBounds();
	//--------------------------------------------------------------------------

	//asigna el sprite del jugador al cuerpo---------------------------------
	PlayerSprite.setPosition(Vector2f(b1.position.x, b1.position.y));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}

		}
		//------------------------------------------------------------------------

			//detienen el salto al tocar el suelo.-----------------
		if (b1.position.y == 290.0f)
		{

			b1.velocity.y = 0.00;
		}
		//-----------------------------------------------------

		//hace saltar al cuerpo si esta en el suelo -----------------------

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			spacep = true;
			airborn = true;
			standing = false;
			cout << " Space is pressed" << endl;

			if (spacep == true)
			{
				b1.velocity.y = -250.0f;
			}
		}
		// si space no esta presionado resetea el bool a false.
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			spacep = false;
			airborn = false;
		}
		//------------------------------------------------------------------


		//moverse a la izquierda ----------------------------------------------------------------

		if (sf::Keyboard::isKeyPressed(Keyboard::A))
		{
			ap = true;
			cout << " Left is pressed" << endl;
			if (ap == true)
			{
				b1.velocity.x = -150.0f;
			}
		}

		// bracket de if responsable por detener el sprite cuando A es presionada.--------------------
		if (ap == true)
		{
			if (!Keyboard::isKeyPressed(Keyboard::A))
			{
				ap = false;
				b1.velocity.x = 0.0f;
			}
		}

		// --------------------------------------------------------------------------------------------

		//Moverse a la derecha-------------------------------------------------------------------------

		if (dp == false) {
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				dp = true;
				b1.velocity.x = 150.0;
				cout << " Right is pressed" << endl;
				if (dp == true)
				{
					b1.velocity.x = 150.0f;
				}
			}
		}
		//bracket responsable por detener el sprited------------
		if (dp == true)
		{
			if (!Keyboard::isKeyPressed(Keyboard::D))
			{
				dp = false;
				b1.velocity.x = 0.0f;
			}
		}

		//-------------------------------------------------------




	//evita que el cuerpo atraviese el piso-------------
		if (b1.position.y >= 290.0f)
		{
			standing = true;
			b1.position.y = 290.0f;
			if (airborn == false)
			{
				b1.velocity.y = 0;
			}

		}
		//--------------------------------------------------

			//lo que hace que pasen los frames y redibuja la pantalla---------------------
		Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();


		world.Step(dt);

		PlayerSprite.setPosition(Vector2f(b1.position.x, b1.position.y));
		window.clear(Color::Transparent);
		window.draw(BG_Sprite);
		window.draw(PlayerSprite);
		window.display();
		//-----------------------------------------------------------------------------
	}

	return 0;
}
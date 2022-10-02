#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	ParticleSystem(unsigned int count, sf::FloatRect targetParticle, float particleSize);

	void setEmitter(sf::Vector2f position);

	void update(sf::Time elapsed);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifeTime;
	};

	void resetParticle(std::size_t index);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::FloatRect m_targetParticles;
	float pSize;
	int m_particlePass = 0;
};

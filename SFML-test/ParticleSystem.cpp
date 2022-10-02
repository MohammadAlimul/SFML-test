#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int count, sf::FloatRect targetParticle, float particleSize) :
	m_particles(count),
	m_vertices(sf::Quads, count * 4),
	m_lifetime(sf::seconds(30.f)),
	m_emitter(0.f, 0.f),
	m_targetParticles(targetParticle),
	pSize(particleSize)
{

}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		Particle& p = m_particles[i];

		p.lifeTime -= elapsed;

		if (p.lifeTime <= sf::Time::Zero)
			resetParticle(i);

		sf::Vertex* quad = &m_vertices[i * 4];

		if (m_targetParticles.intersects(sf::FloatRect(quad[0].position.x, quad[0].position.y, pSize, pSize)))
		{
			resetParticle(i);
			std::cout << m_particlePass++ << "\n";
		}

		sf::Vector2f delta = quad[0].position - sf::Vector2f(m_targetParticles.left, m_targetParticles.top);
		float ratio = delta.y / delta.x;
		float angle = std::atan(ratio);
		if (delta.x < 0)
			angle += 3.14f;
		float speed = 1.f;

		p.velocity -= sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		quad[0].position += p.velocity * elapsed.asSeconds();
		quad[1].position = sf::Vector2f(quad[0].position.x + pSize, quad[0].position.y);
		quad[2].position = sf::Vector2f(quad[0].position.x + pSize, quad[0].position.y + pSize);
		quad[3].position = sf::Vector2f(quad[0].position.x, quad[0].position.y + pSize);

		float ratioLifetime = p.lifeTime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratioLifetime * 255);

	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
	float angle = (std::rand() % 350) * 3.14f / 180.f;
	float speed = (std::rand() % 30) + 20.f;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifeTime = sf::milliseconds((std::rand() % 2000) + 1000);

	sf::Vertex* quad = &m_vertices[index * 4];

	quad[0].color = sf::Color(std::rand() % 200 + 55, std::rand() % 200 + 55, std::rand() % 200 + 55);
	quad[1].color = quad[0].color;
	quad[2].color = quad[0].color;
	quad[3].color = quad[0].color;

	m_vertices[index * 4].position = m_emitter;
}

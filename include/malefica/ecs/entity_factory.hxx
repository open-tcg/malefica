#ifndef MALEFICA_ECS_ENTITY_FACTORY_HXX
#define MALEFICA_ECS_ENTITY_FACTORY_HXX

#include <entt/entity/registry.hpp>

namespace malefica
{
  namespace ecs
  {

    template <typename E, typename = typename std::enable_if<std::is_integral<E>::value, E>::type>
    class base_entity_factory final
    {
      using registry_type = entt::Registry<E>;

    public:
      using size_type = typename registry_type::size_type;
      using entity_type = typename registry_type::entity_type;
      using version_type = typename registry_type::version_type;

      explicit base_entity_factory() noexcept : m_registry_system() {}

      base_entity_factory(const base_entity_factory&) = delete;
      base_entity_factory& operator=(const base_entity_factory&) = delete;
      base_entity_factory(base_entity_factory&&) = delete;
      base_entity_factory& operator=(base_entity_factory&&) = delete;

      inline bool empty() const noexcept { return m_registry_system.empty(); }
      template <typename Component>
      inline bool empty() const noexcept
      {
        return m_registry_system.template empty<Component>();
      }

      inline size_type size() const noexcept { return m_registry_system.size(); }
      template <typename Component>
      inline size_type size() const noexcept
      {
        return m_registry_system.template size<Component>();
      }

      inline bool valid(entity_type entity) const noexcept { return m_registry_system.valid(entity); }
      inline version_type version(entity_type entity) const noexcept { return m_registry_system.version(entity); }
      inline version_type current_version(entity_type entity) const noexcept { return m_registry_system.current(entity); }

      template <typename... Component>
      inline entity_type create() noexcept
      {
        return m_registry_system.template create<Component...>();
      }

      template <typename... Component>
      inline entity_type create(Component&&... components) noexcept
      {
        return m_registry_system.template create<Component...>(std::forward<Component>(components)...);
      }
      inline entity_type create() noexcept { return m_registry_system.create(); }

      inline void destroy(entity_type entity) { return m_registry_system.destroy(entity); }

      template <typename Component, typename... Args>
      inline Component& assign(entity_type entity, Args&&... args)
      {
        return m_registry_system.template accommodate<Component>(entity, std::forward<Args>(args)...);
      }

      template <typename Component>
      void remove(entity_type entity)
      {
        m_registry_system.template remove<Component>(entity);
      }

      template <typename... Component>
      inline bool has(entity_type entity) const noexcept
      {
        return m_registry_system.template has<Component...>(entity);
      }

      template <typename Component>
      void reset(entity_type entity)
      {
        m_registry_system.template reset<Component>(entity);
      }

      template <typename Component>
      void reset()
      {
        m_registry_system.template reset<Component>();
      }

      template <typename Component>
      const Component& get(entity_type entity) const noexcept
      {
        return m_registry_system.template get<Component>(entity);
      }

      template <typename Component>
      Component& get(entity_type entity) noexcept
      {
        return m_registry_system.template get<Component>(entity);
      }

      template <typename... Component>
      std::enable_if_t<(sizeof...(Component) > 1), std::tuple<const Component&...>> get(entity_type entity) const noexcept
      {
        return m_registry_system.template get<Component...>(entity);
      }

      template <typename... Component>
      std::enable_if_t<(sizeof...(Component) > 1), std::tuple<Component&...>> get(entity_type entity) noexcept
      {
        return m_registry_system.template get<Component...>(entity);
      }

    private:
      registry_type m_registry_system;
    };

    using entity_factory = base_entity_factory<std::uint32_t>;

  } // namespace ecs
} // namespace wge

#endif /*MALEFICA_ECS_ENTITY_FACTORY_HXX*/
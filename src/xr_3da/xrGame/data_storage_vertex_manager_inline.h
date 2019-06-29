////////////////////////////////////////////////////////////////////////////
//	Module 		: data_storage_vertex_manager_inline.h
//	Created 	: 21.03.2002
//  Modified 	: 01.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Data storage vertex manager inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

#define TEMPLATE_SPECIALIZATION \
	template <\
		typename _path_id_type,\
		typename _index_type\
	>\
	template <\
		template <typename _T> class _vertex,\
		template <typename _T1, typename _T2> class _index_vertex,\
		typename _data_storage\
	>

#define CDataStorageManager	CDataStorageVertexManager<_path_id_type,_index_type>::CDataStorage<_vertex,_index_vertex,_data_storage>

TEMPLATE_SPECIALIZATION
IC	CDataStorageManager::CDataStorage		(const u32 vertex_count) :
	inherited				(vertex_count),
	m_current_path_id		(_path_id_type(0))
{
}

TEMPLATE_SPECIALIZATION
CDataStorageManager::~CDataStorage		()
{
}

TEMPLATE_SPECIALIZATION
IC	void CDataStorageManager::init		()
{
	inherited::init			();
	m_indexes.clear			();
	++m_current_path_id;
	if (!m_current_path_id)
		++m_current_path_id;
}

TEMPLATE_SPECIALIZATION
IC	void CDataStorageManager::add_opened		(CGraphVertex &vertex)
{
	vertex.opened()			= 1;
}

TEMPLATE_SPECIALIZATION
IC	void CDataStorageManager::add_closed		(CGraphVertex &vertex)
{
	vertex.opened()			= 0;
}

TEMPLATE_SPECIALIZATION
IC	typename CDataStorageManager::_path_id_type CDataStorageManager::current_path_id	() const
{
	return					(m_current_path_id);
}

TEMPLATE_SPECIALIZATION
IC	bool CDataStorageManager::is_opened	(const CGraphVertex &vertex) const
{
	return					(vertex.opened());
}

TEMPLATE_SPECIALIZATION
IC	bool CDataStorageManager::is_visited	(const _index_type &vertex_id) const
{
	_index_map::const_iterator	I = m_indexes.find(&vertex_id);
	if (m_indexes.end() == I)
		return				(false);
	return					(true);
}

TEMPLATE_SPECIALIZATION
IC	bool CDataStorageManager::is_closed	(const CGraphVertex &vertex) const
{
	return					(!is_opened(vertex));
}

TEMPLATE_SPECIALIZATION
IC	typename CDataStorageManager::CGraphVertex &CDataStorageManager::get_node	(const _index_type &vertex_id) const
{
	VERIFY					(is_visited(vertex_id));
	_index_map::const_iterator	I = m_indexes.find(&vertex_id);
	VERIFY					(m_indexes.end() != I);
	return					(*(*I).second.m_vertex);
}

TEMPLATE_SPECIALIZATION
IC	typename CDataStorageManager::CGraphVertex &CDataStorageManager::create_vertex	(CGraphVertex &vertex, const _index_type &vertex_id)
{
	CGraphIndexVertex				index_vertex;
	index_vertex.m_vertex			= &vertex;
	vertex.index()					= vertex_id;
	m_indexes.insert				(std::make_pair(&vertex._index,index_vertex));
	return							(vertex);
}

#undef TEMPLATE_SPECIALIZATION
#undef CDataStorageManager
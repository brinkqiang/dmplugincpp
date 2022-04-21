#ifndef __RAII_DLL_H__
#define __RAII_DLL_H__

/* ����dll�������ԴT��raii�����࣬����ʱ�Զ���ȷ�ͷ���Դ
* TΪ��Դ���ͣ��ⲿ�����޸�
*/
template<typename T>
class raii_dll {
public:
	typedef raii_dll<T> _Self;
	typedef T resource_type;
	/* Ĭ�Ϲ��캯�� */
	raii_dll() :_resource() {}
	/**
	* res ��Դ����
	*/
	explicit raii_dll(const T& res) :
		_resource(res) {
	}
	virtual ~raii_dll() {}
	/* ��ȡ��Դ���� */
	const T& get() const noexcept { return _resource; }
	const T& operator*() const noexcept { return get(); }
	const T& operator()() const noexcept { return get(); }
	/* ��Աָ����������� */
	const T* operator->()const noexcept { return &get(); }
private:
	/* ��װ����Դ�����ⲿ�����޸� */
	T _resource;
}; /* raii_dll */

#endif // !__RAII_DLL_H__

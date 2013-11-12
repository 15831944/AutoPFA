/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Factory.h
  ժҪ��    
  author  : LSP          
*/

#ifndef FACTORY_H
#define FACTORY_H

template
<class abstractProduct,
 class IdentifierType,
 class ProductCreator = abstractProduct*(*)()
>
class CFactory
{
	public:
		void Register(const IdentifierType &id,ProductCreator creator)
		{
			m_assocMap.SetAt(id,creator);
		}

		BOOL UnRegister(const IdentifierType &id)
		{
			return m_assocMap.RemoveKey(id);
		}
		
		abstractProduct* CreatObject(const IdentifierType &id)
		{
			ProductCreator Creator;
			if(m_assocMap.Lookup(id,Creator))
			{
				return (*Creator)();
			}
			else
			{
				return NULL;
			}
		}
		
	private:
		typedef CMap<IdentifierType,IdentifierType,ProductCreator,ProductCreator>AssocMap;
		AssocMap m_assocMap;

};
#endif
		 
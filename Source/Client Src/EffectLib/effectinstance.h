//en alta ekle

protected:
	bool m_ignoreFrustum;

	struct FEffectFrustum
	{
		bool ignoreFrustum;
		FEffectFrustum(bool igno)
			: ignoreFrustum(igno)
		{
		}
		void operator () (CEffectElementBaseInstance * pInstance)
		{
			pInstance->SetIgnoreFrustum(ignoreFrustum);
		}
	};

public:
	void SetIgnoreFrustum(bool frustum)
	{
		m_ignoreFrustum = frustum;
		FEffectFrustum f2(m_ignoreFrustum);
		std::for_each(m_ParticleInstanceVector.begin(), m_ParticleInstanceVector.end(), f2);
		std::for_each(m_MeshInstanceVector.begin(), m_MeshInstanceVector.end(), f2);
		std::for_each(m_LightInstanceVector.begin(), m_LightInstanceVector.end(), f2);
	}
};
/**
 *  @file   PandoraSDK/src/Objects/MCParticle.cc
 * 
 *  @brief  Implementation of the mc particle class.
 * 
 *  $Log: $
 */

#include "Objects/MCParticle.h"

#include <algorithm>

namespace pandora
{

MCParticle::MCParticle(const PandoraApi::MCParticle::Parameters &parameters) :
    m_uid(parameters.m_pParentAddress.Get()),
    m_energy(parameters.m_energy.Get()),
    m_momentum(parameters.m_momentum.Get()),
    m_vertex(parameters.m_vertex.Get()),
    m_endpoint(parameters.m_endpoint.Get()),
    m_innerRadius(parameters.m_vertex.Get().GetMagnitude()),
    m_outerRadius(parameters.m_endpoint.Get().GetMagnitude()),
    m_particleId(parameters.m_particleId.Get()),
    m_mcParticleType(parameters.m_mcParticleType.Get()),
    m_pPfoTarget(NULL)
{
}


//------------------------------------------------------------------------------------------------------------------------------------------

MCParticle::~MCParticle()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::AddDaughter(const MCParticle *const pMCParticle)
{
    if (m_daughterList.end() != std::find(m_daughterList.begin(), m_daughterList.end(), pMCParticle))
        return STATUS_CODE_ALREADY_PRESENT;

    m_daughterList.push_back(pMCParticle);
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::AddParent(const MCParticle *const pMCParticle)
{
    if (m_parentList.end() != std::find(m_parentList.begin(), m_parentList.end(), pMCParticle))
        return STATUS_CODE_ALREADY_PRESENT;

    m_parentList.push_back(pMCParticle);
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::RemoveDaughter(const MCParticle *const pMCParticle)
{
    MCParticleList::iterator iter = std::find(m_daughterList.begin(), m_daughterList.end(), pMCParticle);

    if (m_daughterList.end() == iter)
        return STATUS_CODE_NOT_FOUND;

    m_daughterList.erase(iter);
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::RemoveParent(const MCParticle *const pMCParticle)
{
    MCParticleList::iterator iter = std::find(m_parentList.begin(), m_parentList.end(), pMCParticle);

    if (m_parentList.end() == iter)
        return STATUS_CODE_NOT_FOUND;

    m_parentList.erase(iter);
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::SetPfoTarget(const MCParticle *const pMCParticle)
{
    if (NULL == pMCParticle)
        return STATUS_CODE_FAILURE;

    m_pPfoTarget = pMCParticle;
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MCParticle::RemovePfoTarget()
{
    m_pPfoTarget = NULL;
    return STATUS_CODE_SUCCESS;
}

} // namespace pandora

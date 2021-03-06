/**
 * \brief 皇城争夺战
 *
 * 
 */

#include <zebra/SessionServer.h>

CDareEmperor::CDareEmperor() : CDare(0,0)
{
}

CDareEmperor::CDareEmperor(DWORD active_time,DWORD ready_time) : CDare(active_time,ready_time)
{
}

CDareEmperor::~CDareEmperor()
{
}

void CDareEmperor::setSecondID(DWORD dwID)
{
  this->secondID = dwID;
}

void CDareEmperor::addFirstID(DWORD dwID)
{
}

bool CDareEmperor::isInvalid()
{
  return false;
}

void CDareEmperor::timer()
{
}

void CDareEmperor::setActiveState()
{
  DWORD dwMapID = (NEUTRAL_COUNTRY_ID<<16) + 134;
  Cmd::Session::t_setEmperorDare_SceneSession send;

  // 设置状态
  rwlock.wrlock();
  this->state = CDare::DARE_ACTIVE;
  rwlock.unlock();   

  send.byState = 1;
  send.dwDefCountryID = this->secondID;
  SceneSession *pScene = SceneSessionManager::getInstance()->getSceneByID(dwMapID);
  pScene->sendCmd(&send,sizeof(send));
  SessionChannel::sendAllInfo(Cmd::INFO_TYPE_EXP,"皇城争夺战现在开始，请做好准备。");
}

void CDareEmperor::setReadyOverState()
{
  DWORD dwMapID = (NEUTRAL_COUNTRY_ID<<16) + 134;
  Cmd::Session::t_setEmperorDare_SceneSession send;
  send.byState = 0;
  send.dwDefCountryID = this->secondID;
  SceneSession *pScene = SceneSessionManager::getInstance()->getSceneByID(dwMapID);
  pScene->sendCmd(&send,sizeof(send));

  if (this->dwWinnerID >0)
  {
    CCountry* pCountry = CCountryM::getMe().find(NEUTRAL_COUNTRY_ID);
    pCountry->changeEmperor(this->dwWinnerID);
  
    // 将中立区皇城占领者帮会,设为赢家国家国王所属帮会
    SessionChannel::sendAllInfo(Cmd::INFO_TYPE_EXP,"%s 获得皇城控制权",
        CCountryM::getMe().find(this->dwWinnerID)->name);
  }
  else
  {
    SessionChannel::sendAllInfo(Cmd::INFO_TYPE_EXP,"%s 经过浴血奋战成功守住皇城",
        CCountryM::getMe().find(this->secondID)->name);
  }

  // 通告对战结果
  this->setOverState();
}


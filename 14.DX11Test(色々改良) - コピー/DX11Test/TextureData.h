#pragma once

#include<d3d11.h>
#include"Singleton.h"

class TextureData : public Singleton<TextureData>
{
public:
	friend class Singleton<TextureData>;

public:
	void Initialize();

public:
	ID3D11Resource*           GetBLOCK_TR         ()const { return m_pBLOCK_TR;          }
	ID3D11ShaderResourceView* GetBLOCK_TSRV       ()const { return m_pBLOCK_TSRV;        }
	ID3D11Resource*           GetDOT_FONT_TR      ()const { return m_pDOT_FONT_TR;       }
	ID3D11ShaderResourceView* GetDOT_FONT_TSRV    ()const { return m_pDOT_FONT_TSRV;     }
	ID3D11Resource*           GetCOIN1_TR         ()const { return m_pCOIN1_TR;          }
	ID3D11ShaderResourceView* GetCOIN1_TSRV       ()const { return m_pCOIN1_TSRV;        }
	ID3D11Resource*           GetKOURA1_TR        ()const { return m_pKOURA1_TR;         }
	ID3D11ShaderResourceView* GetKOURA1_TSRV      ()const { return m_pKOURA1_TSRV;       }
	ID3D11Resource*           GetKOURA2_TR        ()const { return m_pKOURA2_TR;         }
	ID3D11ShaderResourceView* GetKOURA2_TSRV      ()const { return m_pKOURA2_TSRV;       }
	ID3D11Resource*           GetKURIBO1_TR       ()const { return m_pKURIBO1_TR;        }
	ID3D11ShaderResourceView* GetKURIBO1_TSRV     ()const { return m_pKURIBO1_TSRV;      }
	ID3D11Resource*           GetKURIBO2_TR       ()const { return m_pKURIBO2_TR;        }
	ID3D11ShaderResourceView* GetKURIBO2_TSRV     ()const { return m_pKURIBO2_TSRV;      }
	ID3D11Resource*           GetKURIBO_DEAD_TR   ()const { return m_pKURIBO_DEAD_TR;    }
	ID3D11ShaderResourceView* GetKURIBO_DEAD_TSRV ()const { return m_pKURIBO_DEAD_TSRV;  }
	ID3D11Resource*           GetMARIO_DEAD_TR    ()const { return m_pMARIO_DEAD_TR;     }
	ID3D11ShaderResourceView* GetMARIO_DEAD_TSRV  ()const { return m_pMARIO_DEAD_TSRV;   }
	ID3D11Resource*           GetMARIO_JUMP_TR    ()const { return m_pMARIO_JUMP_TR;     }
	ID3D11ShaderResourceView* GetMARIO_JUMP_TSRV  ()const { return m_pMARIO_JUMP_TSRV;   }
	ID3D11Resource*           GetMARIO_RUN1_TR    ()const { return m_pMARIO_RUN1_TR;     }
	ID3D11ShaderResourceView* GetMARIO_RUN1_TSRV  ()const { return m_pMARIO_RUN1_TSRV;   }
	ID3D11Resource*           GetMARIO_RUN2_TR    ()const { return m_pMARIO_RUN2_TR;     }
	ID3D11ShaderResourceView* GetMARIO_RUN2_TSRV  ()const { return m_pMARIO_RUN2_TSRV;   }
	ID3D11Resource*           GetMARIO_RUN3_TR    ()const { return m_pMARIO_RUN3_TR;     }
	ID3D11ShaderResourceView* GetMARIO_RUN3_TSRV  ()const { return m_pMARIO_RUN3_TSRV;   }
	ID3D11Resource*           GetMARIO_STAND_TR   ()const { return m_pMARIO_STAND_TR;    }
	ID3D11ShaderResourceView* GetMARIO_STAND_TSRV ()const { return m_pMARIO_STAND_TSRV;  }
	ID3D11Resource*           GetNOKONOKO1_TR     ()const { return m_pNOKONOKO1_TR;      }
	ID3D11ShaderResourceView* GetNOKONOKO1_TSRV   ()const { return m_pNOKONOKO1_TSRV;    }
	ID3D11Resource*           GetNOKONOKO2_TR     ()const { return m_pNOKONOKO2_TR;      }
	ID3D11ShaderResourceView* GetNOKONOKO2_TSRV   ()const { return m_pNOKONOKO2_TSRV;    }
	ID3D11Resource*           GetTITLE_LOGO_TR    ()const { return m_pTITLE_LOGO_TR;     }
	ID3D11ShaderResourceView* GetTITLE_LOGO_TSRV  ()const { return m_pTITLE_LOGO_TSRV;   }
	ID3D11Resource*           GetBLOCK_GROUND_TR  ()const { return m_pBLOCK_GROUND_TR;   }
	ID3D11ShaderResourceView* GetBLOCK_GROUND_TSRV()const { return m_pBLOCK_GROUND_TSRV; }
	ID3D11Resource*           GetGOAL_PIN_TR      ()const { return m_pGOAL_PIN_TR;       }
	ID3D11ShaderResourceView* GetGOAL_PIN_TSRV    ()const { return m_pGOAL_PIN_TSRV;     }
	ID3D11Resource*           GetGOAL_POLE_TR     ()const { return m_pGOAL_POLE_TR;      }
	ID3D11ShaderResourceView* GetGOAL_POLE_TSRV   ()const { return m_pGOAL_POLE_TSRV;    }
	ID3D11Resource*           GetGOAL_FLAG_TR     ()const { return m_pGOAL_FLAG_TR;      }
	ID3D11ShaderResourceView* GetGOAL_FLAG_TSRV   ()const { return m_pGOAL_FLAG_TSRV;    }
	ID3D11Resource*           GetGOAL_CASTLE_TR   ()const { return m_pGOAL_CASTLE_TR;    }
	ID3D11ShaderResourceView* GetGOAL_CASTLE_TSRV ()const { return m_pGOAL_CASTLE_TSRV;  }
	ID3D11Resource*           GetCLAY_PIPE_TR     ()const { return m_pCLAY_PIPE_TR;      }
	ID3D11ShaderResourceView* GetCLAY_PIPE_TSRV   ()const { return m_pCLAY_PIPE_TSRV;    }

private:
	ID3D11Resource*           m_pBLOCK_TR          = nullptr;
    ID3D11ShaderResourceView* m_pBLOCK_TSRV        = nullptr;
	ID3D11Resource*           m_pDOT_FONT_TR       = nullptr;
	ID3D11ShaderResourceView* m_pDOT_FONT_TSRV     = nullptr;
	ID3D11Resource*           m_pCOIN1_TR          = nullptr;
	ID3D11ShaderResourceView* m_pCOIN1_TSRV        = nullptr;
	ID3D11Resource*           m_pKOURA1_TR         = nullptr;
	ID3D11ShaderResourceView* m_pKOURA1_TSRV       = nullptr;
	ID3D11Resource*           m_pKOURA2_TR         = nullptr;
	ID3D11ShaderResourceView* m_pKOURA2_TSRV       = nullptr;
	ID3D11Resource*           m_pKURIBO1_TR        = nullptr;
	ID3D11ShaderResourceView* m_pKURIBO1_TSRV      = nullptr;
	ID3D11Resource*           m_pKURIBO2_TR        = nullptr;
	ID3D11ShaderResourceView* m_pKURIBO2_TSRV      = nullptr;
	ID3D11Resource*           m_pKURIBO_DEAD_TR    = nullptr;
	ID3D11ShaderResourceView* m_pKURIBO_DEAD_TSRV  = nullptr;
	ID3D11Resource*           m_pMARIO_DEAD_TR     = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_DEAD_TSRV   = nullptr;
	ID3D11Resource*           m_pMARIO_JUMP_TR     = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_JUMP_TSRV   = nullptr;
	ID3D11Resource*           m_pMARIO_RUN1_TR     = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_RUN1_TSRV   = nullptr;
	ID3D11Resource*           m_pMARIO_RUN2_TR     = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_RUN2_TSRV   = nullptr;
	ID3D11Resource*           m_pMARIO_RUN3_TR     = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_RUN3_TSRV   = nullptr;
	ID3D11Resource*           m_pMARIO_STAND_TR    = nullptr;
	ID3D11ShaderResourceView* m_pMARIO_STAND_TSRV  = nullptr;
	ID3D11Resource*           m_pNOKONOKO1_TR      = nullptr;
	ID3D11ShaderResourceView* m_pNOKONOKO1_TSRV    = nullptr;
	ID3D11Resource*           m_pNOKONOKO2_TR      = nullptr;
	ID3D11ShaderResourceView* m_pNOKONOKO2_TSRV    = nullptr;
	ID3D11Resource*           m_pTITLE_LOGO_TR     = nullptr;
	ID3D11ShaderResourceView* m_pTITLE_LOGO_TSRV   = nullptr;
	ID3D11Resource*           m_pBLOCK_GROUND_TR   = nullptr;
	ID3D11ShaderResourceView* m_pBLOCK_GROUND_TSRV = nullptr;
	ID3D11Resource*           m_pGOAL_PIN_TR       = nullptr;
	ID3D11ShaderResourceView* m_pGOAL_PIN_TSRV     = nullptr;
	ID3D11Resource*           m_pGOAL_POLE_TR      = nullptr;
	ID3D11ShaderResourceView* m_pGOAL_POLE_TSRV    = nullptr;
	ID3D11Resource*           m_pGOAL_FLAG_TR      = nullptr;
	ID3D11ShaderResourceView* m_pGOAL_FLAG_TSRV    = nullptr;
	ID3D11Resource*           m_pGOAL_CASTLE_TR    = nullptr;
	ID3D11ShaderResourceView* m_pGOAL_CASTLE_TSRV  = nullptr;
	ID3D11Resource*           m_pCLAY_PIPE_TR = nullptr;
	ID3D11ShaderResourceView* m_pCLAY_PIPE_TSRV = nullptr;

private:
	TextureData() {};
	TextureData(const TextureData &gameManager) {};
	~TextureData();

protected:
	bool m_InitializedFlag = false;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	void Abstract() {};  //純粋仮想関数（これによってこのクラスはインスタンスできない)
};
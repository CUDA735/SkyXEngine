
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
Заголовочный файл render_func - пространства имен с орагнизацией рендера*/

/*! \defgroup managed_render_render_func render_func - пространство имен с орагнизацией рендера
 \ingroup managed_render
@{*/

#ifndef __render_func
#define __render_func

#include <GRegisterIndex.h>

/*! \name Состояния рендера
@{*/

#define RENDER_STATE_MATERIAL	0	/*!< отрисовка материалов */
#define RENDER_STATE_SHADOW		1	/*!< отрисовка теней */
#define RENDER_STATE_FREE		2	/*!< простая отрисовка (не материальная) */

//!@}

/*! \name Идентификаторы для определяния типа просчетов видимости
@{*/

#define RENDER_IDARRCOM_GEOM	0	/*!< геометрия */
#define RENDER_IDARRCOM_GREEN	1	/*!< растительность */
#define RENDER_IDARRCOM_ANIM	2	/*!< анимации */

//!@}

#define RENDER_PARTICLES_ALPHATEST_VALUE 16	/*!< минимальное значение для альфа теста */

/*! \name Идентификаторы для определяния типа просчетов видимости
@{*/

#define RENDER_LAYER_NULL			0	/*!< нулевой (пустой слой, здесь будут к примеру скайбокс, облака и т.д.) */
#define RENDER_LAYER_UNTRANSPARENT	1	/*!< непрозрачный слой */
#define RENDER_LAYER_TRANSPARENT	2	/*!< первый прозрачный слой, следующие слои могут быть прозрачными */

//!@}

//! пространство имен с орагнизацией рендера
namespace SXRenderFunc
{
	//быстрая реализация фильтрации и адресации
	//{
	//индифидуально для регистра
	inline void SetSamplerFilter(DWORD id, DWORD value);
	inline void SetSamplerAddress(DWORD id, DWORD value);
	
	//для указанного промежутка групп регистров
	inline void SetSamplerFilter(DWORD begin_id, DWORD end_id, DWORD value);
	inline void SetSamplerAddress(DWORD begin_id, DWORD end_id, DWORD value);

	void SetRenderSceneFilter();
	void SetRenderSceneFilterUn();
	//}

	//! обработка потери и восстановление устройства
	void ComDeviceLost();

	void UpdateDataCVar();

	void UpdateView();						//!< обработка и установка основных матриц, обработка плоскостей отсечения
	void OutputDebugInfo(DWORD timeDelta);	//!< вывод отладочной текстовой информации в окно рендера

	void ComVisibleForLight();				//!< обработка видимости для источников света
	void ComVisibleForCamera();				//!< обработка видимости для камеры
	void ComVisibleReflection();			//!< обработка видимости для отражений

	void RenderInMRT(DWORD timeDelta);		//!< построение G буфера, то есть рендер всей сцены
	void UpdateShadow(DWORD timeDelta);		//!< обновление информации о тенях (рендер всего того что отбрасывает тени в буферы глубин источников света)
	void UpdateReflection(DWORD timeDelta);	//!< обработка/обновление отражений
	
	void RenderSky(DWORD timeDelta);					//!< отрисовка скайбокса и облаков
	void ComLighting(DWORD timeDelta, bool render_sky);	//!< обработка освещения, render_sky - рисовать ли небо
	void RenderParticles(DWORD timeDelta);				//!< отрисовка партиклов (эффектов)
	void RenderPostProcess(DWORD timeDelta);			//!< отрисовка постпроцесса
	void ShaderRegisterData();

	void RenderEditorMain();				//!< рендер основных элементов для редакторов
	void RenderEditorLE(DWORD timeDelta);	//!< рендер элементов для редактора уровней
	
	/*! \name Функции обертки, для передачи графическому ядру для замены стандартных
	@{*/

	//! функция отрисовки, в данной версии не назначается
	void RFuncDIP(UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
	//! функция установки материала по id, world - мировая матрица
	void RFuncMtlSet(ID id, float4x4* world);
	//! функция загрузки материала
	ID RFuncMtlLoad(const char* name, int mtl_type);
	
	//!@}

	bool AIQuadPhyNavigate(float3_t * pos);

	void SaveScreenShot();		//!< сохранить скриншот
	void SaveWorkTex();			//!< сохранить рабочие текстуры (г-буфер и что к нему прилагается)
	void ChangeModeWindow();	//!< изменить режим рендера (оконный/полноэкранный)

	//! время задержек/ожидания выполнения некоторых функций рендера
	namespace Delay
	{
		int64_t UpdateVisibleForCamera = 0;
		int64_t UpdateVisibleForLight = 0;
		int64_t UpdateVisibleForReflection = 0;

		int64_t UpdateShadow = 0;
		int64_t UpdateParticles = 0;
		int64_t RenderMRT = 0;
		int64_t ComLighting = 0;
		int64_t PostProcess = 0;
		int64_t ComReflection = 0;
		int64_t GeomSortGroup = 0;

		int64_t Present = 0;

		int64_t FreeVal = 0;
		float FreeValF1 = 0;
		float FreeValF2 = 0;
		float FreeValF3 = 0;
	};
};

#endif

//!@} managed_render_render_func

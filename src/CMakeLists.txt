target_sources(im_app
    PRIVATE
    	Formula.cpp
    	Formula.h
    	Kb.cpp
    	Kb.h
    	Parser.cpp
    	Parser.h
      	Utils.cpp
      	Utils.h
	ComputeMIS.h
	ComputeMIS.cpp
	ComputeMCS.h
	ComputeMCS.cpp
	InconsistencyMeasureASP.h
	InconsistencyMeasureASP.cpp
	LTLMeasuresASP.h
	LTLMeasuresASP.cpp
	MISBasedInconsistencyMeasures.h
	MISBasedInconsistencyMeasures.cpp
	MCSBasedInconsistencyMeasures.h
	MCSBasedInconsistencyMeasures.cpp
	Constants.h
)

target_include_directories(im_app PUBLIC ${CMAKE_CURRENT_LIST_DIR})

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
		InconsistencyMeasureASP.h
		InconsistencyMeasureASP.cpp
		LTLMeasuresASP.h
		LTLMeasuresASP.cpp
		Constants.h
)

target_include_directories(im_app PUBLIC ${CMAKE_CURRENT_LIST_DIR})

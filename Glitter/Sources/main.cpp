#include "hello_rect.h"
#include "shaders_uniform.h"
#include "shaders_interpolation.h"
#include "shaders_class.h"
#include <iostream>
#include <windows.h>
#include "textures.h"
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "transformations.h"
#include "coordinate_systems.h"
#include "hello_camera.h"
#include "Colors.h"
#include "basic_lighting_diffuse.h"
#include "materials.h"
#include "lighting_maps_diffuse.h"
#include "lighting_maps_specular_map.h"



int main() {
        
/*    hello_triangle hw;
    hw.hello_triangleOpenGL(); */   

    //hello_rect hr;
    //hr.hello_rectOpenGL();

    //shaders_uniform su;
    //su.shaders_uniformOpenGL();

    //shaders_interpolation si;
    //si.run();

    //shaderClass sc;
    //sc.run();

    //textures tx;
    //tx.run();
    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //// ��ע��������Ǿ����ʼ����һ�����ӣ����ʹ�õ���0.9.9�����ϰ汾
    //// �������д������Ҫ��Ϊ:
    //// glm::mat4 trans = glm::mat4(1.0f)
    //// ֮�󽫲��ٽ�����ʾ
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //vec = trans * vec;
    //std::cout << vec.x << vec.y << vec.z << std::endl;

    //transformations ts;
    //ts.run();
    //coordinate_systems cs;
    //cs.run();

    //camera cm;
    //cm.run();

    //Colors col;
    //col.run();

    //basic_lighting_diffuse bld;
    //bld.run();

    //materials mat;
    //mat.run();

    //lighting_maps_diffuse lmd;
    //lmd.run();
    
    lighting_maps_specular_map lmsm;
    lmsm.run();
	


}



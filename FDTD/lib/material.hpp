//
//  material.hpp
//  FDTD
//
//  Created by Robbie Alexander on 18/12/2023.
//

#ifndef material_hpp
#define material_hpp

class Material
{
private:
    float* epsilon;
    float* mu;
public:
    Material();
    Material(float*, float*);
    ~Material();
};

#endif /* material_hpp */

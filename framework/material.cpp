//
// Created by Polina on 03.07.2024.
//
#include "material.hpp"

std::ostream& Material::print(std::ostream &os) const {
    os<<"name: "<< name_<<"\n"
      <<"ka: "<<ka_<<"\n"
      <<"kd: "<<kd_<<"\n"
      <<"ks: "<<ks_<<"\n"
      <<"m: "<<m_<<std::endl;
    return os;
}

std::ostream& operator<<(std::ostream &os,Material const& m) {
    return m.print(os);
}
Material::Material(const std::string& name, Color const& ka, Color const& kd, Color const& ks, float m)
        : name_(name), ka_(ka),kd_(kd), ks_(ks),m_(m) {};
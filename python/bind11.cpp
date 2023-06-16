#include <pybind11/pybind11.h>
#include "../main.cpp"

namespace py=pybind11;

PYBIND11_MODULE(Quat, m){
  // py::class_<Quat> quat(m, "Quat");
  // quat.def(py::init<double, double, double, double>());
  // quat.def("x", &Quat::x);
  // quat.def("y", &Quat::y);
  // quat.def("z", &Quat::z);
  // quat.def("w", &Quat::w);
  // quat.def("norm", &Quat::norm);
  // quat.def("conj", &Quat::conj);
  // quat.def("inv",&Quat::inv);
  // quat.def("rot",&Quat::rot);
  // quat.def("to_eular", &Quat::to_eular);
  // quat.def("to__mat", &Quat::to__mat);
  // quat.def(py::self + py::self);
  // quat.def(py::self + float());
  // quat.def(py::self - py::self);
  // quat.def(py::self - float());
  // quat.def(py::self * py::self);
  // quat.def(py::self * float());
  // quat.def(py::self / py::self);
  // quat.def(py::self / float());
}



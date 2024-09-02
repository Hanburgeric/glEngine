#include "importer.h"

#include <fstream>
#include <iterator>
#include <map>

#include <filereadstream.h>
#include <glad/gl.h>

#include "utils.h"

void Importer::LoadASCIIFromFile(GLTF& gltf, const std::string& path) {
  LoadDocument(path);
  LoadAccessors(gltf);
  LoadAnimations(gltf);
  LoadBuffers(gltf, path);
  LoadBufferViews(gltf);
//  LoadCameras(gltf);
//  LoadImages(gltf);
//  LoadMaterials(gltf);
  LoadMeshes(gltf);
  LoadNodes(gltf);
//  LoadSamplers(gltf);
  LoadScene(gltf);
  LoadScenes(gltf);
//  LoadSkins(gltf);
//  LoadTextures(gltf);
}

void Importer::LoadDocument(const std::string& path) {
  FILE* file = fopen(path.c_str(), "rb");
  char buffer[65536];
  rapidjson::FileReadStream stream(file, buffer, sizeof(buffer));
  (void)this->document_.ParseStream(stream);
  (void)fclose(file);
}

void Importer::LoadAccessors(GLTF& gltf) {
  if (this->document_.HasMember("accessors")) {
    for (const auto& accessor : this->document_["accessors"].GetArray()) {
      Accessor new_accessor;

      //Buffer View
      if (accessor.HasMember("bufferView")) {
        new_accessor.buffer_view_ = accessor["bufferView"].GetInt();
      } else {
        new_accessor.buffer_view_ = -1;
      }

      //Byte Offset
      if (accessor.HasMember("byteOffset")) {
        new_accessor.byte_offset_ = accessor["byteOffset"].GetInt();
      } else {
        new_accessor.byte_offset_ = 0;
      }

      //Component Type
      new_accessor.component_type_ = accessor["componentType"].GetInt();

      //Normalized
      if (accessor.HasMember("normalized")) {
        new_accessor.normalized_ = accessor["normalized"].GetBool();
      } else {
        new_accessor.normalized_ = false;
      }

      //Count
      new_accessor.count_ = accessor["count"].GetInt();

      //Type
      new_accessor.type_ = accessor["type"].GetString();

      //Max
      if (accessor.HasMember("max")) {
        CopyGenericArrayToVector(new_accessor.max_, accessor["max"].GetArray());
      }

      //Min
      if (accessor.HasMember("min")) {
        CopyGenericArrayToVector(new_accessor.max_, accessor["max"].GetArray());
      }

//      //Sparse
//      if (accessor.HasMember("sparse")) {
//      }

      //Name
      if (accessor.HasMember("name")) {
        new_accessor.name_ = accessor["name"].GetString();
      }

      //Add Accessor
      gltf.accessors_.push_back(new_accessor);
    }
  }
}

void Importer::LoadAnimations(GLTF& gltf) {
  if (this->document_.HasMember("animations")) {
    for (const auto& animation : this->document_["animations"].GetArray()) {
      Animation new_animation;

      //Channels
      for (const auto& channel : animation["channels"].GetArray()) {
        AnimationChannel new_channel;

        //Sampler
        new_channel.sampler_ = channel["sampler"].GetInt();

        //Target
        const rapidjson::Value& target = channel["target"];
        AnimationChannelTarget& new_target = new_channel.target_;

        //Node
        if (target.HasMember("node")) {
          new_target.node_ = target["node"].GetInt();
        } else {
          new_target.node_ = -1;
        }

        //Path
        new_target.path_ = target["path"].GetString();

        //Add Channel
        new_animation.channels_.push_back(new_channel);
      }

      //Samplers
      for (const auto& sampler : animation["samplers"].GetArray()) {
        AnimationSampler new_sampler;

        //Input
        new_sampler.input_ = sampler["input"].GetInt();

        //Interpolation
        if (sampler.HasMember("interpolation")) {
          new_sampler.interpolation_ = sampler["interpolation"].GetString();
        } else {
          new_sampler.interpolation_ = "LINEAR";
        }

        //Output
        new_sampler.output_ = sampler["output"].GetInt();

        //Add Sampler
        new_animation.samplers_.push_back(new_sampler);
      }

      //Name
      if (animation.HasMember("name")) {
        new_animation.name_ = animation["name"].GetString();
      }

      //Add Animation
      gltf.animations_.push_back(new_animation);
    }
  }
}

void Importer::LoadBuffers(GLTF& gltf, const std::string& file_path) {
  if (this->document_.HasMember("buffers")) {
    for (const auto& buffer : this->document_["buffers"].GetArray()) {
      Buffer new_buffer;

      //URI
      if (buffer.HasMember("uri")) {
        new_buffer.uri_ = buffer["uri"].GetString();
      }

      //Byte Length
      new_buffer.byte_length_ = buffer["byteLength"].GetInt();

      //Name
      if (buffer.HasMember("name")) {
        new_buffer.name_ = buffer["name"].GetString();
      }

      //Data
      if (!new_buffer.uri_.empty()) {
        std::ifstream data(file_path.substr(0U, file_path.find_last_of("/\\")) + "/" + new_buffer.uri_, std::ios::binary);
        new_buffer.data_ = std::vector<char>(std::istreambuf_iterator<char>(data), {});
      }

      //Add Buffer
      gltf.buffers_.push_back(new_buffer);
    }
  }
}

void Importer::LoadBufferViews(GLTF& gltf) {
  if (this->document_.HasMember("bufferViews")) {
    for (const auto& buffer_view : this->document_["bufferViews"].GetArray()) {
      BufferView new_buffer_view;

      //Buffer
      new_buffer_view.buffer_ = buffer_view["buffer"].GetInt();

      //Byte Offset
      if (buffer_view.HasMember("byteOffset")) {
        new_buffer_view.byte_offset_ = buffer_view["byteOffset"].GetInt();
      } else {
        new_buffer_view.byte_offset_ = 0;
      }

      //Byte Length
      new_buffer_view.byte_length_ = buffer_view["byteLength"].GetInt();

      //Byte Stride
      if (buffer_view.HasMember("byteStride")) {
        new_buffer_view.byte_stride_ = buffer_view["byteStride"].GetInt();
      } else {
        new_buffer_view.byte_stride_ = 0;
      }

      //Target
      if (buffer_view.HasMember("target")) {
        new_buffer_view.target_ = buffer_view["target"].GetInt();
      } else {
        new_buffer_view.target_ = 0;
      }

      //Name
      if (buffer_view.HasMember("name")) {
        new_buffer_view.name_ = buffer_view["name"].GetString();
      }

      //Add Buffer View
      gltf.buffer_views_.push_back(new_buffer_view);
    }
  }
}

void Importer::LoadMeshes(GLTF& gltf) {
  if (this->document_.HasMember("meshes")) {
    for (const auto& mesh : this->document_["meshes"].GetArray()) {
      Mesh new_mesh;

      //Primitives
      for (const auto& primitive : mesh["primitives"].GetArray()) {
        MeshPrimitive new_primitive;

        //Attributes
        for (const auto& attribute : primitive["attributes"].GetObject()) {
          (void)new_primitive.attributes_.emplace(attribute.name.GetString(), attribute.value.GetInt());
        }

        //Indices
        if (primitive.HasMember("indices")) {
          new_primitive.indices_ = primitive["indices"].GetInt();
        } else {
          new_primitive.indices_ = -1;
        }

        //Material
        if (primitive.HasMember("material")) {
          new_primitive.material_ = primitive["material"].GetInt();
        } else {
          new_primitive.material_ = -1;
        }

        //Mode
        if (primitive.HasMember("mode")) {
          new_primitive.mode_ = primitive["mode"].GetInt();
        } else {
          new_primitive.mode_ = 4;
        }

        //Targets
        if (primitive.HasMember("targets")) {
          for (const auto& target : primitive["targets"].GetArray()) {
            std::map<std::string, std::int32_t> new_attribute;
            for (const auto& attribute : target.GetObject()) {
              (void)new_attribute.emplace(attribute.name.GetString(), attribute.value.GetInt());
            }
            new_primitive.targets_.push_back(new_attribute);
          }
        }

        //VAO
        glGenVertexArrays(1, &new_primitive.vao_);
        glBindVertexArray(new_primitive.vao_);

        //VBOS
        for (const auto& attribute : new_primitive.attributes_) {
          const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(attribute.second)];
          const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
          const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];

          new_primitive.vbos_.push_back(0U);
          std::uint32_t& vbo = new_primitive.vbos_.back();
          glGenBuffers(1, &vbo);
          glBindBuffer(GL_ARRAY_BUFFER, vbo);
          glBufferData(GL_ARRAY_BUFFER,
                       buffer_view.byte_length_,
                       &buffer.data_[static_cast<std::size_t>(buffer_view.byte_offset_ + accessor.byte_offset_)],
                       static_cast<GLenum>(GL_DYNAMIC_DRAW));

          auto index = static_cast<std::uint32_t>(new_primitive.vbos_.size() - 1U);
          glVertexAttribPointer(index, GetNumComponentsInType(accessor),
                                static_cast<GLenum>(accessor.component_type_),
                                accessor.normalized_,
                                GetByteStride(accessor, buffer_view),
                                static_cast<char*>(nullptr) + accessor.byte_offset_);
          glEnableVertexAttribArray(index);
        }

        //EBOS
        if (new_primitive.indices_ >= 0) {
          const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(new_primitive.indices_)];
          const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
          const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];

          glGenBuffers(1, &new_primitive.ebo_);
          glBindBuffer(static_cast<GLenum>(GL_ELEMENT_ARRAY_BUFFER), new_primitive.ebo_);
          glBufferData(static_cast<GLenum>(GL_ELEMENT_ARRAY_BUFFER),
                       buffer_view.byte_length_,
                       &buffer.data_[static_cast<std::size_t>(buffer_view.byte_offset_ + accessor.byte_offset_)],
                       static_cast<GLenum>(GL_DYNAMIC_DRAW));
        }

        //Add Mesh Primitive
        new_mesh.primitives_.push_back(new_primitive);
      }

      //Weights
      if (mesh.HasMember("weights")) {
        CopyGenericArrayToVector(new_mesh.weights_, mesh["weights"].GetArray());
      }

      //Name
      if (mesh.HasMember("name")) {
        new_mesh.name_ = mesh["name"].GetString();
      }

      //Add Mesh
      gltf.meshes_.push_back(new_mesh);
    }
  }
}

void Importer::LoadNodes(GLTF& gltf) {
  if (this->document_.HasMember("nodes")) {
    for (const auto& node : this->document_["nodes"].GetArray()) {
      Node new_node;

      //Camera
      if (node.HasMember("camera")) {
        new_node.camera_ = node["camera"].GetInt();
      } else {
        new_node.camera_ = -1;
      }

      //Children
      if (node.HasMember("children")) {
        CopyGenericArrayToVector(new_node.children_, node["children"].GetArray());
      }

      //Skin
      if (node.HasMember("skin")) {
        new_node.skin_ = node["skin"].GetInt();
      } else {
        new_node.skin_ = -1;
      }

      //Matrix
      if (node.HasMember("matrix")) {
        CopyGenericArrayToArray(new_node.matrix_, node["matrix"].GetArray());
      } else {
        for (std::size_t row = 0U; row < 4U; row++) {
          for (std::size_t col = 0U; col < 4U; col++) {
            std::size_t index = col * 4U + row;
            new_node.matrix_[index] = row == col ? 1.0F : 0.0F;
          }
        }
      }

      //Mesh
      if (node.HasMember("mesh")) {
        new_node.mesh_ = node["mesh"].GetInt();
      } else {
        new_node.mesh_ = -1;
      }

      //Rotation
      if (node.HasMember("rotation")) {
        CopyGenericArrayToArray(new_node.rotation_, node["rotation"].GetArray());
      } else {
        new_node.rotation_[0U] = 0.0F;
        new_node.rotation_[1U] = 0.0F;
        new_node.rotation_[2U] = 0.0F;
        new_node.rotation_[3U] = 1.0F;
      }

      //Scale
      if (node.HasMember("scale")) {
        CopyGenericArrayToArray(new_node.scale_, node["scale"].GetArray());
      } else {
        new_node.scale_[0U] = 1.0F;
        new_node.scale_[1U] = 1.0F;
        new_node.scale_[2U] = 1.0F;
      }

      //Translation
      if (node.HasMember("translation")) {
        CopyGenericArrayToArray(new_node.translation_, node["translation"].GetArray());
      } else {
        new_node.translation_[0U] = 0.0F;
        new_node.translation_[1U] = 0.0F;
        new_node.translation_[2U] = 0.0F;
      }

      //Weights
      if (node.HasMember("weights")) {
        CopyGenericArrayToVector(new_node.weights_, node["weights"].GetArray());
      }

      //Name
      if (node.HasMember("name")) {
        new_node.name_ = node["name"].GetString();
      }

      //Add Node
      gltf.nodes_.push_back(new_node);
    }
  }
}

void Importer::LoadScene(GLTF& gltf) {
  if (this->document_.HasMember("scene")) {
    gltf.scene_ = this->document_["scene"].GetInt();
  } else {
    gltf.scene_ = -1;
  }
}

void Importer::LoadScenes(GLTF& gltf) {
  if (this->document_.HasMember("scenes")) {
    for (const auto& scene : this->document_["scenes"].GetArray()) {
      Scene new_scene;

      //Nodes
      if (scene.HasMember("nodes")) {
        CopyGenericArrayToVector(new_scene.nodes_, scene["nodes"].GetArray());
      }

      //Name
      if (scene.HasMember("name")) {
        new_scene.name_ = scene["name"].GetString();
      }

      //Add Scene
      gltf.scenes_.push_back(new_scene);
    }
  }
}

#define STB_IMAGE_IMPLEMENTATION

#include "importer.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>

#include <filereadstream.h>
#include <glad/gl.h>
#include <stb_image.h>

#include "utils.h"

void Importer::LoadASCIIFromFile(GLTF& gltf, const std::string& path) {
  LoadDocument(path);
  LoadAccessors(gltf);
  LoadAnimations(gltf);
  LoadBuffers(gltf);
  LoadBufferViews(gltf);
//  LoadCameras(gltf);
  LoadImages(gltf);
  LoadMaterials(gltf);
  LoadMeshes(gltf);
  LoadNodes(gltf);
  LoadSamplers(gltf);
  LoadScene(gltf);
  LoadScenes(gltf);
//  LoadSkins(gltf);
  LoadTextures(gltf);
  Initialize(gltf);
}

void Importer::LoadDocument(const std::string& path) {
  //Parent Directory
  parent_directory_ = GetBaseDir(path);

  //Document
  FILE* file = fopen(path.c_str(), "rb");
  char buffer[65536U];
  rapidjson::FileReadStream stream(file, buffer, sizeof(buffer));
  (void)document_.ParseStream(stream);
  (void)fclose(file);
}

void Importer::LoadAccessors(GLTF& gltf) {
  gltf.accessors_.clear();
  if (document_.HasMember("accessors")) {
    for (const auto& accessor : document_["accessors"].GetArray()) {
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

      //Sparse
      if (accessor.HasMember("sparse")) {
        const rapidjson::Value& accessor_sparse = accessor["sparse"];
        AccessorSparse& new_accessor_sparse = new_accessor.sparse_;

        //Count
        new_accessor_sparse.count_ = accessor_sparse["count"].GetInt();

        //Indices
        const rapidjson::Value& accessor_sparse_indices = accessor_sparse["indices"];
        AccessorSparseIndices& new_accessor_sparse_indices = new_accessor_sparse.indices_;

        //Buffer View
        new_accessor_sparse_indices.buffer_view_ = accessor_sparse_indices["bufferView"].GetInt();

        //Byte Offset
        if (accessor_sparse_indices.HasMember("byteOffset")) {
          new_accessor_sparse_indices.byte_offset_ = accessor_sparse_indices["byteOffset"].GetInt();
        } else {
          new_accessor_sparse_indices.byte_offset_ = 0;
        }

        //Component Type
        new_accessor_sparse_indices.component_type_ = accessor_sparse_indices["componentType"].GetInt();

        //Values
        const rapidjson::Value& accessor_sparse_values = accessor_sparse["values"];
        AccessorSparseValues& new_accessor_sparse_values = new_accessor_sparse.values_;

        //Buffer View
        new_accessor_sparse_values.buffer_view_ = accessor_sparse_values["bufferView"].GetInt();

        //Byte Offset
        if (accessor_sparse_indices.HasMember("byteOffset")) {
          new_accessor_sparse_values.byte_offset_ = accessor_sparse_values["byteOffset"].GetInt();
        } else {
          new_accessor_sparse_values.byte_offset_ = 0;
        }
      }

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
  gltf.animations_.clear();
  if (document_.HasMember("animations")) {
    for (const auto& animation : document_["animations"].GetArray()) {
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

void Importer::LoadBuffers(GLTF& gltf) {
  gltf.buffers_.clear();
  if (document_.HasMember("buffers")) {
    for (const auto& buffer : document_["buffers"].GetArray()) {
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

      //Add Buffer
      gltf.buffers_.push_back(new_buffer);
    }
  }
}

void Importer::LoadBufferViews(GLTF& gltf) {
  gltf.buffer_views_.clear();
  if (document_.HasMember("bufferViews")) {
    for (const auto& buffer_view : document_["bufferViews"].GetArray()) {
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

void Importer::LoadImages(GLTF& gltf) {
  gltf.images_.clear();
  if (document_.HasMember("images")) {
    for (const auto& image : document_["images"].GetArray()) {
      Image new_image;

      //URI
      if (image.HasMember("uri")) {
        new_image.uri_ = image["uri"].GetString();
      }

      //Mime Type
      if (image.HasMember("mimeType")) {
        new_image.mime_type_ = image["mimeType"].GetString();
      }

      //Buffer View
      if (image.HasMember("bufferView")) {
        new_image.buffer_view_ = image["bufferView"].GetInt();
      } else {
        new_image.buffer_view_ = -1;
      }

      //Name
      if (image.HasMember("name")) {
        new_image.name_ = image["name"].GetString();
      }

      //Add Mesh
      gltf.images_.push_back(new_image);
    }
  }
}

void Importer::LoadMaterials(GLTF& gltf) {
  gltf.materials_.clear();
  if (document_.HasMember("materials")) {
    for (const auto& material : document_["materials"].GetArray()) {
      Material new_material;

      //Name
      if (material.HasMember("name")) {
        new_material.name_ = material["name"].GetString();
      }

      //PBR Metallic Roughness
      if (material.HasMember("pbrMetallicRoughness")) {
        const auto pbr_metallic_roughness = material["pbrMetallicRoughness"].GetObject();
        MaterialPBRMetallicRoughness& new_pbr_metallic_roughness = new_material.pbr_metallic_roughness_;

        //Base Color Factor
        if (pbr_metallic_roughness.HasMember("baseColorFactor")) {
          CopyGenericArrayToArray(new_pbr_metallic_roughness.base_color_factor_,
                                  pbr_metallic_roughness["baseColorFactor"].GetArray());
        } else {
          new_pbr_metallic_roughness.base_color_factor_[0U] = 1.0F;
          new_pbr_metallic_roughness.base_color_factor_[1U] = 1.0F;
          new_pbr_metallic_roughness.base_color_factor_[2U] = 1.0F;
          new_pbr_metallic_roughness.base_color_factor_[3U] = 1.0F;
        }

        //Base Color Texture
        if (pbr_metallic_roughness.HasMember("baseColorTexture")) {
          const auto base_color_texture = pbr_metallic_roughness["baseColorTexture"].GetObject();
          TextureInfo& new_base_color_texture = new_pbr_metallic_roughness.base_color_texture_;

          //Index
          new_base_color_texture.index_ = base_color_texture["index"].GetInt();

          //Tex Coord
          if (base_color_texture.HasMember("texCoord")) {
            new_base_color_texture.tex_coord_ = base_color_texture["texCoord"].GetInt();
          } else {
            new_base_color_texture.tex_coord_ = 0;
          }
        }

        //Metallic Factor
        if (pbr_metallic_roughness.HasMember("metallicFactor")) {
          new_pbr_metallic_roughness.metallic_factor_ = pbr_metallic_roughness["metallicFactor"].GetFloat();
        } else {
          new_pbr_metallic_roughness.metallic_factor_ = 1.0F;
        }

        //Roughness Factor
        if (pbr_metallic_roughness.HasMember("roughnessFactor")) {
          new_pbr_metallic_roughness.roughness_factor_ = pbr_metallic_roughness["roughnessFactor"].GetFloat();
        } else {
          new_pbr_metallic_roughness.roughness_factor_ = 1.0F;
        }

        //Metallic Roughness Texture
        if (pbr_metallic_roughness.HasMember("metallicRoughnessTexture")) {
          const auto metallic_roughness_texture = pbr_metallic_roughness["metallicRoughnessTexture"].GetObject();
          TextureInfo& new_metallic_roughness_texture = new_pbr_metallic_roughness.metallic_roughness_texture_;

          //Index
          new_metallic_roughness_texture.index_ = metallic_roughness_texture["index"].GetInt();

          //Tex Coord
          if (metallic_roughness_texture.HasMember("texCoord")) {
            new_metallic_roughness_texture.tex_coord_ = metallic_roughness_texture["texCoord"].GetInt();
          } else {
            new_metallic_roughness_texture.tex_coord_ = 0;
          }
        }
      }

      //Normal Texture
      if (material.HasMember("normalTexture")) {
        const auto normal_texture = material["normalTexture"].GetObject();
        MaterialNormalTextureInfo& new_normal_texture = new_material.normal_texture_;

        //Index
        new_normal_texture.index_ = normal_texture["index"].GetInt();

        //Tex Coord
        if (normal_texture.HasMember("texCoord")) {
          new_normal_texture.tex_coord_ = normal_texture["texCoord"].GetInt();
        } else {
          new_normal_texture.tex_coord_ = 0;
        }

        //Scale
        if (normal_texture.HasMember("scale")) {
          new_normal_texture.scale_ = normal_texture["scale"].GetFloat();
        } else {
          new_normal_texture.scale_ = 1.0F;
        }
      }

      //Occlusion Texture
      if (material.HasMember("occlusionTexture")) {
        const auto occlusion_texture = material["occlusionTexture"].GetObject();
        MaterialOcclusionTextureInfo& new_occlusion_texture = new_material.occlusion_texture_;

        //Index
        new_occlusion_texture.index_ = occlusion_texture["index"].GetInt();

        //Tex Coord
        if (occlusion_texture.HasMember("texCoord")) {
          new_occlusion_texture.tex_coord_ = occlusion_texture["texCoord"].GetInt();
        } else {
          new_occlusion_texture.tex_coord_ = 0;
        }

        //Strength
        if (occlusion_texture.HasMember("strength")) {
          new_occlusion_texture.strength_ = occlusion_texture["strength"].GetFloat();
        } else {
          new_occlusion_texture.strength_ = 1.0F;
        }
      }

      //Emissive Texture
      if (material.HasMember("emissiveTexture")) {
        const auto emissive_texture = material["emissiveTexture"].GetObject();
        TextureInfo& new_emissive_texture = new_material.emissive_texture_;

        //Index
        new_emissive_texture.index_ = emissive_texture["index"].GetInt();

        //Tex Coord
        if (emissive_texture.HasMember("texCoord")) {
          new_emissive_texture.tex_coord_ = emissive_texture["texCoord"].GetInt();
        } else {
          new_emissive_texture.tex_coord_ = 0;
        }
      }

      //Emissive Factor
      if (material.HasMember("emissiveFactor")) {
        CopyGenericArrayToArray(new_material.emissive_factor_, material["emissiveFactor"].GetArray());
      } else {
        new_material.emissive_factor_[0U] = 0.0F;
        new_material.emissive_factor_[1U] = 0.0F;
        new_material.emissive_factor_[2U] = 0.0F;
      }

      //Alpha Mode
      if (material.HasMember("alphaMode")) {
        new_material.alpha_mode_ = material["alphaMode"].GetString();
      } else {
        new_material.alpha_mode_ = "OPAQUE";
      }

      //Alpha Cutoff
      if (material.HasMember("alphaCutoff")) {
        new_material.alpha_cutoff_ = material["alphaCutoff"].GetFloat();
      } else {
        new_material.alpha_cutoff_ = 0.5F;
      }

      //Double Sided
      if (material.HasMember("doubleSided")) {
        new_material.double_sided_ = material["doubleSided"].GetBool();
      } else {
        new_material.double_sided_ = false;
      }

      //Add Material
      gltf.materials_.push_back(new_material);
    }
  }
}

void Importer::LoadMeshes(GLTF& gltf) {
  gltf.meshes_.clear();
  if (document_.HasMember("meshes")) {
    for (const auto& mesh : document_["meshes"].GetArray()) {
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
            std::unordered_map<std::string, std::int32_t> new_attribute;
            for (const auto& attribute : target.GetObject()) {
              (void)new_attribute.emplace(attribute.name.GetString(), attribute.value.GetInt());
            }
            new_primitive.targets_.push_back(new_attribute);
          }
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
  gltf.nodes_.clear();
  if (document_.HasMember("nodes")) {
    for (const auto& node : document_["nodes"].GetArray()) {
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

void Importer::LoadSamplers(GLTF& gltf) {
  gltf.samplers_.clear();
  if (document_.HasMember("samplers")) {
    for (const auto& sampler : document_["samplers"].GetArray()) {
      Sampler new_sampler;

      //Mag Filter
      if (sampler.HasMember("magFilter")) {
        new_sampler.mag_filter_ = sampler["magFilter"].GetInt();
      } else {
        new_sampler.mag_filter_ = -1;
      }

      //Min Filter
      if (sampler.HasMember("minFilter")) {
        new_sampler.min_filter_ = sampler["minFilter"].GetInt();
      } else {
        new_sampler.min_filter_ = -1;
      }

      //Wrap S
      if (sampler.HasMember("wrapS")) {
        new_sampler.wrap_s_ = sampler["wrapS"].GetInt();
      } else {
        new_sampler.wrap_s_ = 10497;
      }

      //Wrap T
      if (sampler.HasMember("wrapT")) {
        new_sampler.wrap_t_ = sampler["wrapT"].GetInt();
      } else {
        new_sampler.wrap_t_ = 10497;
      }

      //Name
      if (sampler.HasMember("name")) {
        new_sampler.name_ = sampler["name"].GetString();
      }

      //Add Sampler
      gltf.samplers_.push_back(new_sampler);
    }
  }
}

void Importer::LoadScene(GLTF& gltf) {
  if (document_.HasMember("scene")) {
    gltf.scene_ = document_["scene"].GetInt();
  } else {
    gltf.scene_ = -1;
  }
}

void Importer::LoadScenes(GLTF& gltf) {
  gltf.scenes_.clear();
  if (document_.HasMember("scenes")) {
    for (const auto& scene : document_["scenes"].GetArray()) {
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

void Importer::LoadTextures(GLTF& gltf) {
  gltf.textures_.clear();
  if (document_.HasMember("textures")) {
    for (const auto& texture : document_["textures"].GetArray()) {
      Texture new_texture;

      //Sampler
      if (texture.HasMember("sampler")) {
        new_texture.sampler_ = texture["sampler"].GetInt();
      } else {
        new_texture.sampler_ = -1;
      }

      //Source
      if (texture.HasMember("source")) {
        new_texture.source_ = texture["source"].GetInt();
      } else {
        new_texture.source_ = -1;
      }

      //Name
      if (texture.HasMember("name")) {
        new_texture.name_ = texture["name"].GetString();
      }

      //Add Texture
      gltf.textures_.push_back(new_texture);
    }
  }
}

void Importer::Initialize(GLTF& gltf) {
  //Buffer
  for (auto& buffer : gltf.buffers_) {
    //Data
    if (!buffer.uri_.empty()) {
      std::ifstream data(parent_directory_ + buffer.uri_, std::ios::binary);
      buffer.data_ = std::vector<uint8_t>(std::istreambuf_iterator<char>(data), {});
    }
  }

  //Mesh
  for (auto& mesh : gltf.meshes_) {
    for (auto& primitive : mesh.primitives_) {
      //VAO
      glGenVertexArrays(1, &primitive.vao_);
      glBindVertexArray(primitive.vao_);

      //VBOS
      for (const auto& attribute : primitive.attributes_) {
        const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(attribute.second)];
        const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
        const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];

        primitive.vbos_.push_back(0U);
        std::uint32_t& vbo = primitive.vbos_.back();
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     buffer_view.byte_length_,
                     &buffer.data_[static_cast<std::size_t>(buffer_view.byte_offset_) +
                     static_cast<std::size_t>(accessor.byte_offset_)],
                     static_cast<GLenum>(GL_DYNAMIC_DRAW));

        auto index = static_cast<std::uint32_t>(primitive.vbos_.size() - 1U);
        glVertexAttribPointer(index, GetNumComponentsInType(accessor),
                              static_cast<GLenum>(accessor.component_type_),
                              accessor.normalized_,
                              GetByteStride(accessor, buffer_view),
                              static_cast<char*>(nullptr) + accessor.byte_offset_);
        glEnableVertexAttribArray(index);
      }

      //EBO
      if (primitive.indices_ >= 0) {
        const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(primitive.indices_)];
        const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
        const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];

        glGenBuffers(1, &primitive.ebo_);
        glBindBuffer(static_cast<GLenum>(GL_ELEMENT_ARRAY_BUFFER), primitive.ebo_);
        glBufferData(static_cast<GLenum>(GL_ELEMENT_ARRAY_BUFFER),
                     buffer_view.byte_length_,
                     &buffer.data_[static_cast<std::size_t>(buffer_view.byte_offset_) +
                     static_cast<std::size_t>(accessor.byte_offset_)],
                     static_cast<GLenum>(GL_DYNAMIC_DRAW));
      }
    }
  }

  //Image
  for (auto& image : gltf.images_) {
    //Data
    if (!image.uri_.empty()) {
      std::ifstream data(parent_directory_ + image.uri_, std::ios::binary);
      image.data_ = std::vector<uint8_t>(std::istreambuf_iterator<char>(data), {});
    }
  }

  //Texture
  for (auto& texture : gltf.textures_) {
    //Texture
    Sampler sampler;
    if (texture.sampler_ < 0) {
      sampler.mag_filter_ = -1;
      sampler.min_filter_ = -1;
      sampler.wrap_s_ = 10497;
      sampler.wrap_t_ = 10497;
    } else {
      sampler = gltf.samplers_[static_cast<std::size_t>(texture.sampler_)];
    }

    Image image;
    if (texture.source_ < 0) {
    } else {
      image = gltf.images_[static_cast<std::size_t>(texture.source_)];
    }

    std::int32_t x;
    std::int32_t y;
    std::int32_t comp;
    std::uint8_t* data = stbi_load_from_memory(image.data_.data(),
                                               static_cast<std::int32_t>(image.data_.size()), &x, &y, &comp, 0);
    if (data != nullptr) {
      int format;
      if (comp == 1) {
        format = GL_RED;
      } else if (comp == 3) {
        format = GL_RGB;
      } else {
        format = GL_RGBA;
      }
      glGenTextures(1, &texture.texture_);
      glBindTexture(GL_TEXTURE_2D, texture.texture_);
      glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, static_cast<GLenum>(format), GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), sampler.mag_filter_);
      glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), sampler.min_filter_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrap_s_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sampler.wrap_t_);
    } else {
      std::cerr << "Failed to load texture at: " << parent_directory_ + image.uri_ << std::endl;
    }
    stbi_image_free(data);
  }

  //Animation
  for (auto& animation : gltf.animations_) {
    //Interpolators
    animation.interpolators_ = std::vector<Interpolator>(animation.channels_.size(), Interpolator());

    //Max Time
    animation.max_time_ = 0.0F;
    for (const auto& channel : animation.channels_) {
      const AnimationSampler& sampler = animation.samplers_[static_cast<std::size_t>(channel.sampler_)];
      const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(sampler.input_)];
      const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
      const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];
      std::int32_t byte_offset = buffer_view.byte_offset_ + accessor.byte_offset_;
      auto input = reinterpret_cast<const float*>(&buffer.data_[static_cast<std::size_t>(byte_offset)]);
      auto input_length = static_cast<std::size_t>(accessor.count_ * GetNumComponentsInType(accessor));
      float max = input[input_length - 1U];
      if (max > animation.max_time_) {
        animation.max_time_ = max;
      }
    }
  }
}

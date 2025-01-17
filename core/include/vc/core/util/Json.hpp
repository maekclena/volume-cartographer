#pragma once

/**
 * @file Json.hpp
 * JSON serialization/deserialization type specializations.
 */

#include <nlohmann/json.hpp>
#include <opencv2/core.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN
/* cv::Vec */
template <typename T, int Cn>
struct adl_serializer<cv::Vec<T, Cn>> {
    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void to_json(JsonT& j, const cv::Vec<T, Cn>& v)
    {
        for (int i = 0; i < Cn; i++) {
            j.push_back(v[i]);
        }
    }

    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void from_json(const JsonT& j, cv::Vec<T, Cn>& v)
    {
        for (int i = 0; i < Cn; i++) {
            v[i] = j.at(i).template get<T>();
        }
    }
};

/* cv::Mat_ */
template <typename T>
struct adl_serializer<cv::Mat_<T>> {
    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void to_json(JsonT& j, const cv::Mat_<T>& m)
    {
        for (int r = 0; r < m.rows; r++) {
            json row;
            for (int c = 0; c < m.cols; c++) {
                row.push_back(m(r, c));
            }
            j.push_back(row);
        }
    }

    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void from_json(const JsonT& j, cv::Mat_<T>& m)
    {
        auto rows = j.size();
        auto cols = j[0].size();
        m = cv::Mat_<T>(rows, cols);
        for (int r = 0; r < m.rows; r++) {
            for (int c = 0; c < m.cols; c++) {
                m(r, c) = j[r][c];
            }
        }
    }
};

/* cv::Matx */
template <typename T, int M, int N>
struct adl_serializer<cv::Matx<T, M, N>> {
    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void to_json(JsonT& j, const cv::Matx<T, M, N>& mat)
    {
        for (int r = 0; r < M; r++) {
            JsonT row;
            for (int c = 0; c < N; c++) {
                row.push_back(mat(r, c));
            }
            j.push_back(row);
        }
    }

    template <class JsonT>
    // NOLINTNEXTLINE(readability-identifier-naming): Must be exact signature
    static void from_json(const JsonT& j, cv::Matx<T, M, N>& mat)
    {
        for (int r = 0; r < M; r++) {
            for (int c = 0; c < N; c++) {
                mat(r, c) = j[r][c];
            }
        }
    }
};
NLOHMANN_JSON_NAMESPACE_END
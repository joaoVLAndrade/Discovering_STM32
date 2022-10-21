#pragma once

typedef enum cbf_status_s
{
    CBF_OK = 0, /**< Operação realizada com sucesso */
    CBF_FULL,   /**< Buffer circular cheio */
    CBF_EMPTY,  /**< Buffer circular vazio */
} cbf_status_t;

typedef struct cbf_s
{
	volatile uint16_t prod; /**< Indicador da posição de produção no buffer circular */
	volatile uint16_t cons; /**< Indicador da posição de consumo no buffer circular */
	uint16_t size;          /**< Tamanho total do buffer circular */
    uint8_t *buffer;        /**< Ponteiro para a área de dados do buffer circular (alocado pelo usuário) */
} cbf_t;


/**
 @brief Retorna a quantidade de bytes disponível para consumo num buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @return quantidade de bytes disponível para consumo
*/
uint16_t cbf_bytes_available(cbf_t *cb);
/**
 @brief Esvazia um buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @return ver @ref cbf_status_s
*/
cbf_status_t cbf_flush(cbf_t *cb);
/**
 @brief Retira um byte do buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @param[out] c - ponteiro para o destino do dado (previamente alocado).
 @return ver @ref cbf_status_s
*/
cbf_status_t cbf_get(cbf_t *cb, uint8_t *c);
/**
 @brief Reinicializa um buffer circular, caso seja necessário.
 @param[in] cb - ponteiro para o buffer circular.
 @param[in] area - buffer previamente alocado que será usado para armazenamento do conteúdo do buffer circular.
 @param[in] size - tamanho da área de dados apontada por @p area.
 @return ver @ref cbf_status_s
*/
cbf_status_t cbf_init(cbf_t *cb, uint8_t *area, uint16_t size);
/**
 @brief Coloca um byte no buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @param[in] c - byte a ser adicionado ao buffer circular.
 @return ver @ref cbf_status_s
*/
cbf_status_t cbf_put(cbf_t *cb, uint8_t c);


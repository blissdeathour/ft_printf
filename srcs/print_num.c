/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhilary <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:39:47 by fhilary           #+#    #+#             */
/*   Updated: 2020/02/10 18:39:50 by fhilary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	num_prec_zero(t_pf *pf)
{
	if ((pf->flag & PLUS_FLAG) || (pf->flag & SPACE_FLAG))
		pf->width--;
	if (!(pf->flag & MIN_FLAG) && pf->width > 0)
		print_padding_add_len(' ', &(pf->width), pf);
	if (pf->flag & PLUS_FLAG)
		pf->len += ft_putchar('+');
	if (pf->flag & SPACE_FLAG)
		pf->len += ft_putchar(' ');
	if (pf->width > 0)
		ft_putcharn(' ', pf->width);
}

void	print_zero_flag_space_plus_flag(t_pf *pf, char **tmp)
{
	if ((*tmp)[0] == '-')
	{
		pf->len += ft_putchar('-');
		(*tmp)++;
	}
	else if (pf->flag & PLUS_FLAG)
		pf->len += ft_putchar('+');
	else if (pf->flag & SPACE_FLAG)
		pf->len += ft_putchar(' ');
}

void	print_zero_flag_num(t_pf *pf, int *diff, char *tmp)
{
	if (tmp[0] == '-')
		pf->width--;
	if (((pf->flag & PLUS_FLAG) || (pf->flag & SPACE_FLAG)) && tmp[0] != '-')
		(*diff)--;
	if (pf->precision == -1 && pf->data_type != 'f' && pf->data_type != 'F')
		pf->precision = (int)ft_strlen(tmp);
	while (pf->precision > 0 && pf->width > pf->precision
	&& (pf->data_type != 'f' && pf->data_type != 'F') && *diff > 0)
	{
		pf->len += ft_putchar(' ');
		pf->width--;
		(*diff)--;
	}
	print_zero_flag_space_plus_flag(pf, &tmp);
	while ((*diff) > 0)
	{
		pf->len += ft_putchar('0');
		(*diff)--;
	}
	print_precision(pf, tmp);
	pf->len += ft_putstr(tmp);
}

void	print_no_zero_flag_num(t_pf *pf, int *diff, char *tmp)
{
	if (!(pf->flag & MIN_FLAG))
		print_padding_add_len(' ', diff, pf);
	print_plus_space_flag(pf, tmp);
	if (tmp[0] == '-')
	{
		pf->len += ft_putchar('-');
		print_precision(pf, tmp);
		pf->len += ft_putstr(tmp + 1);
	}
	else
	{
		print_precision(pf, tmp);
		pf->len += ft_putstr(tmp);
	}
	print_padding_add_len(' ', diff, pf);
}

void	print_num_d(t_pf *pf, long long num)
{
	int		diff;
	char	*tmp;

	if (!num && pf->precision == -1)
	{
		num_prec_zero(pf);
		return ;
	}
	tmp = ft_lltoa(num);
	if (!tmp)
		display_error("Out of memory");
	diff = calc_diff(pf, tmp);
	if (pf->flag & ZERO_FLAG)
		print_zero_flag_num(pf, &diff, tmp);
	else
		print_no_zero_flag_num(pf, &diff, tmp);
	free(tmp);
}
